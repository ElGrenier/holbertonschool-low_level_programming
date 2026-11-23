# Analyse Valgrind : aliasing_example.c

Commande :

    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./aliasing_example

Résultat : 3 erreurs, 3 contextes, aucune fuite.

## Cycle de vie du bloc concerné (commun aux 3 erreurs)

| Événement | Source dans la sortie Valgrind | Ligne |
|---|---|---|
| Allocation de 20 octets (5 int) | "Block was alloc'd at ... make_numbers" | 12 (appelé depuis main, ligne 30) |
| Libération | "free'd at ... main" | 38 |
| Accès invalides via `b` | trois erreurs ci-dessous | 42, 44, 45 |

Le bloc est à l'adresse 0x4a86480 (`a` et `b` contiennent cette valeur).
Les alias `a` et `b` désignent ce même bloc ; `free(a)` le libère pour les deux.

## Erreur 1 : Invalid read of size 4 (ligne 42, `b[2]`)

- Type : use-after-free (lecture).
- Objet : le bloc heap de 20 octets alloué ligne 12.
- Adresse lue : 0x4a86488 = 0x4a86480 + 8, soit l'octet 8 du bloc,
  c'est-à-dire `b[2]` (2 x 4 octets). Valgrind l'indique : "8 bytes inside a
  block of size 20 free'd".
- Violation : la durée de vie du bloc s'est terminée au `free(a)` (ligne 38).
  `b` est un alias de `a` qui n'a pas été invalidé : il contient toujours
  l'adresse, mais cette adresse n'appartient plus au programme.

## Erreur 2 : Invalid write of size 4 (ligne 44, `b[3] = 1234`)

- Type : use-after-free (écriture).
- Objet : le même bloc, à l'adresse 0x4a8648c = 0x4a86480 + 12 = `b[3]`.
- Violation : écriture dans de la mémoire déjà rendue à l'allocateur. C'est
  plus grave qu'une lecture : cette écriture peut corrompre les structures de
  l'allocateur ou les données d'un autre bloc qui réutiliserait cet espace.

## Erreur 3 : Invalid read of size 4 (ligne 45, relecture de `b[3]`)

- Type : use-after-free (lecture), même adresse que l'erreur 2.
- Pourquoi une erreur distincte : l'écriture de la ligne 44 ne "répare" rien.
  Chaque accès à de la mémoire libérée est signalé séparément, car les
  instructions concernées sont différentes (trois contextes distincts).

## Ce que Valgrind ne signale pas

- Ligne 40 (`printf` de la valeur de `b`) : aucune erreur. Valgrind surveille
  les accès à la mémoire (lire ou écrire des octets), pas l'usage de la valeur
  d'un pointeur. GCC, lui, avait signalé cette ligne à la compilation. Les
  deux outils ne détectent pas la même chose : l'analyse statique de GCC
  suit la valeur du pointeur, Valgrind observe les accès réels.
- Fuite mémoire : "All heap blocks were freed". Le bloc a été libéré une
  fois, donc le bug n'est pas un leak. Une absence de fuite ne signifie pas
  absence de bug.
- Mémoire non initialisée : aucune erreur de ce type, donc l'option
  `--track-origins=yes` n'a rien eu à tracer ici.

## Observation : valeur lue différente de l'exécution normale

| Exécution | Valeur affichée pour `b[2]` |
|---|---|
| Normale | -1781134091 |
| Sous Valgrind | 22 |

Sous Valgrind, `malloc` et `free` sont remplacés par ceux de Valgrind. Le
bloc libéré est conservé sans être réutilisé, donc les anciens octets (22)
sont toujours là. Dans l'exécution normale, l'allocateur de la glibc a
modifié ces octets. La cause exacte côté glibc reste une hypothèse non
vérifiée : Valgrind ne peut pas la confirmer, justement parce qu'il remplace
l'allocateur.

## Erreur de l'IA : Valgrind pouvait vérifier mon hypothèse

### Ce que l'IA a affirmé

L'IA a écrit que son explication de la valeur -1781134091 (réutilisation des
premiers octets du bloc libéré par la glibc) serait "vérifiable avec
Valgrind".

### Pourquoi c'est faux

Valgrind remplace l'allocateur du programme. La sortie ci-dessus le prouve :
`b[2]` vaut 22 sous Valgrind, contre -1781134091 en exécution normale. Valgrind
détecte l'accès invalide, mais il change le comportement qu'on voulait
expliquer.

### Correction

Valgrind sert à identifier et localiser l'accès invalide (type, adresse,
offset dans le bloc, lignes d'allocation et de libération). Il ne sert pas à
expliquer ce que contient la mémoire libérée dans une exécution normale, qui
est un comportement indéfini dépendant de l'allocateur.



# Analyse Valgrind : heap_example.c

Commande :

    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./heap_example

Résultat : 1 erreur, 1 contexte. Aucune erreur d'accès (pas d'invalid read/write,
pas de valeur non initialisée).

## Structure des données

`person_new` fait deux allocations indépendantes pour une seule `Person` :

    STACK (main)           HEAP
    alice ----------->  [struct Person : name ---+, age=30]   (ligne 14)
                                                 |
                                                 +--> ["Alice\0"] 6 octets (ligne 21)

Le seul pointeur vers le texte du nom est le champ `name` stocké dans la struct.
Le propriétaire du texte est donc la struct.

## Erreur : 6 bytes in 1 blocks are definitely lost

- Type : fuite mémoire (memory leak), classée "definitely lost".
- Objet : le bloc de 6 octets contenant `"Alice\0"` (5 caractères + `'\0'`),
  alloué ligne 21 (`p->name = malloc(len + 1)`), dans l'appel
  `person_new("Alice", 30)` de la ligne 51 de `main`.
- Résumé du bilan : 5 allocations, 4 libérations, 6 octets en cours d'utilisation
  à la sortie.

### Pourquoi la fuite se produit

1. `alice` est libérée par `person_free_partial(alice)` (ligne 41 : `free(p)`).
   Cette fonction libère la struct mais pas `p->name`.
2. À cet instant, la struct est rendue à l'allocateur et le champ `name`
   disparaît avec elle.
3. Le bloc `"Alice\0"` est toujours alloué, mais aucun pointeur du programme ne
   contient plus son adresse : il est impossible de le `free`.

C'est une fuite par perte de propriété (leak due to lost ownership) : le
propriétaire (la struct) a été libéré avant ce qu'il possédait.

### Pourquoi `bob` ne fuit pas

`main` fait `free(bob->name)` puis `free(bob)`. L'ordre compte : on libère le
contenu avant le conteneur, car après `free(bob)` il serait invalide de lire
`bob->name`. Les 4 libérations sont : nom de bob, struct de bob, struct
d'alice, et un bloc supplémentaire (voir ci-dessous).

### Pourquoi "definitely lost" et pas "indirectly lost" ni "still reachable"

- Pas "still reachable" : aucun pointeur ne mène plus au bloc à la sortie.
- Pas "indirectly lost" : cette catégorie s'applique à un bloc dont le seul
  pointeur se trouve dans un autre bloc lui-même perdu. Ici la struct a été
  libérée, elle n'est pas "perdue". Si on avait oublié aussi `free(alice)`,
  la struct serait "definitely lost" et le nom "indirectly lost".

### Ce que Valgrind indique et ce qu'il n'indique pas

Valgrind indique où le bloc perdu a été alloué (ligne 21, depuis la ligne 51),
mais pas où le `free` manquait. C'est à l'analyse de le déduire : `free(p)` de
`person_free_partial` (ligne 41) ne libère pas `p->name`.

### Total d'octets alloués

1 066 octets alloués au total. Détail probable : 2 structs (2 x 16 octets,
`sizeof(Person)` valant 16 avec le padding), 6 + 4 octets pour les noms, soit
42 octets, et 1 024 octets qui ne viennent pas du code : vraisemblablement le
tampon de sortie de `printf`, alloué par la bibliothèque C (hypothèse non
vérifiée). Ce 5e bloc est libéré à la fin, ce qui explique 5 allocations pour
4 libérations avec un seul bloc perdu.

## Prédiction vs résultat

L'IA avait prédit : 6 octets "definitely lost", alloués ligne 21, aucun accès
invalide, 1 erreur au total. La sortie Valgrind confirme cette prédiction.