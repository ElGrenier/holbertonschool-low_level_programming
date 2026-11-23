
# stack_example 

## Ce que fait le programme

main appelle walk_stack(0, 3), qui s'appelle elle-même jusqu'à depth = 3. À chaque niveau, walk_stack appelle dump_frame("enter", depth) avant de descendre, et dump_frame("exit", depth) après être remontée. Il n'y a aucun malloc : tout est sur la stack.

## Les moments clés

## Moment 1 : dans walk_stack(0,3), avant le premier dump_frame

STACK (adresses hautes en haut, la stack grandit vers le bas sur x86-64)

```
main            : (pas de variable locale)
walk_stack #0   : depth=0, max_depth=3, marker=0
```

## Moment 2 : dans dump_frame("enter", 0)

main
walk_stack #0   : depth=0, marker=0
dump_frame #0   : depth=0, local_int=100, local_buf="A", p_local = &local_int
                  (p_local pointe vers local_int, DANS LA MÊME frame)

Ici, le pointeur et la variable pointée sont tous les deux sur la stack. Aucun heap.

## Moment 3 : dump_frame retourne, sa frame disparaît.  
On est revenu à l'état du moment 1, puis walk_stack(1,3) est appelée.

## Moment 4 : le plus profond, dans walk_stack(3,3)

```
main
walk_stack #0   : depth=0, marker=0     <- adresse la plus haute
walk_stack #1   : depth=1, marker=10
walk_stack #2   : depth=2, marker=20
walk_stack #3   : depth=3, marker=30    <- adresse la plus basse
   (dump_frame #3 apparaît ici temporairement : local_int=103, local_buf="D")
```

Comme depth == max_depth, il n'y a plus d'appel récursif.

## Moment 5 : la remontée.  
Après chaque retour, une frame walk_stack est détruite, mais celle du dessus (l'appelante) est intacte, donc ses marker valent toujours leurs valeurs d'origine. Chaque dump_frame("exit", d) recrée une frame temporaire.

**Durées de vie**
| Variable |	Où |	Vit jusqu'à |
|:-------- |:--------:| --------:|
| `depth`, `max_depth`, `marker` | frame de `walk_stack` | la fin de cet appel |
| `local_int`, `local_buf`, `p_local` |	frame de `dump_frame` |	la fin de cet appel de `dump_frame` |


# Erreur de l'IA : frames décrites de façon incomplète

### Ce que l'IA a affirmé

Pour `stack_example.c`, l'IA a représenté chaque frame de `walk_stack` avec
seulement les variables visibles dans le code source :

    walk_stack #1 : depth=1, max_depth=3, marker=10

Elle a donc implicitement présenté une frame comme "l'ensemble de ses
variables locales et paramètres".

### Pourquoi c'est incomplet

Les paramètres et variables de `walk_stack` (`depth`, `max_depth`,
`marker`) représentent 3 × 4 = 12 octets. Or la sortie réelle du programme
montre un écart de 0x30 = 48 octets entre deux niveaux de récursion :

    &marker (depth=0) = 0x7ffc77b5acec
    &marker (depth=1) = 0x7ffc77b5acbc     0xacec - 0xacbc = 0x30 = 48 octets
    &marker (depth=2) = 0x7ffc77b5ac8c     0xacbc - 0xac8c = 0x30 = 48 octets
    &marker (depth=3) = 0x7ffc77b5ac5c     0xac8c - 0xac5c = 0x30 = 48 octets

Une frame occupe donc 36 octets de plus que les variables visibles dans le code.
Ces octets ne sont pas "perdus" : ils contiennent des données gérées par le
compilateur et le processeur, absentes du code C. Le même phénomène existe
dans `dump_frame` : `local_buf` occupe 16 octets (de `...aca0` à `...acaf`),
`local_int` est à `...acb4`, et il reste donc 4 octets (`...acb0` à
`...acb3`) qui ne correspondent à aucune variable du code.

### Ce qui occupe vraisemblablement ces octets

Ce que prouve la sortie : l'écart de 48 octets est supérieur aux 12 octets de
variables. Le détail ci-dessous est une explication probable, pas une preuve :

- l'adresse de retour (8 octets sur x86-64), empilée par l'instruction `call`,
  qui indique où reprendre dans l'appelante ;
- l'ancien pointeur de frame (`rbp`) sauvegardé (8 octets) ;
- du padding d'alignement (la stack doit rester alignée sur 16 octets
  aux appels de fonction) ;
- possiblement une valeur de protection de la stack (canary) ajoutée par
  le compilateur, car `marker` a son adresse prise (`&marker`).

### Comment j'ai corrigé mes schémas

Dans mes memory maps, chaque frame contient désormais, en plus des variables
du code, une zone "gestion de la frame" :

    walk_stack #1 (48 octets au total)
    +---------------------------------------------+
    | marker=10, depth=1, max_depth=3 (12 octets) |
    | padding / canary / ancien rbp / adresse de  |
    | retour (invisible dans le code C)           |
    +---------------------------------------------+

### Leçon

Une frame n'est pas seulement un ensemble de variables locales : c'est une
zone de taille réelle mesurable, dont une partie est invisible dans le code C.
Une explication qui ne dessine que les variables du code ne peut pas expliquer
les adresses réellement observées.




# Analyse de aliasing_example.c

## Compilation

Le `make` standard échoue : GCC détecte les utilisations de `b` après
`free(a)` (`-Werror=use-after-free`, lignes 40, 42, 44 et 45) et `-Werror`
transforme ces avertissements en erreurs. J'ai donc compilé sans `-Werror` :

    gcc -Wall -Wextra -pedantic -std=gnu89 -g -o aliasing_example aliasing_example.c

Sortie obtenue :

    a=0x25df9420 b=0x25df9420 a[2]=22 b[2]=22
    after free(a): b=0x25df9420 (dangling)
    reading b[2]=-1781134091
    wrote b[3]=1234

## Étapes et memory maps

Notation : `0xH` = 0x25df9420, l'adresse du bloc heap observée à l'exécution.
Les adresses du heap (0x25df...) sont très différentes de celles de la stack
(0x7ffc...) vues dans `stack_example` : ce sont deux zones distinctes.

### Étape 1 : début de `main`

    STACK (main)               HEAP
    a = NULL
    b = NULL                   (aucun bloc)
    n = 5

### Étape 2 : dans `make_numbers(5)`, après `malloc`

    STACK
    main          : a = NULL, b = NULL, n = 5
    make_numbers  : n = 5 (copie), i = 0, arr = 0xH ---+
                                                       |
    HEAP                                               v
    bloc de 20 octets (5 x 4) à 0xH : [??][??][??][??][??]   non initialisé

Le `n` de `make_numbers` est une copie : c'est une variable différente du `n`
de `main`.

### Étape 3 : après la boucle `for`

    HEAP, bloc à 0xH : [0][11][22][33][44]
                        [0] [1] [2] [3] [4]   (arr[i] = i * 11)

### Étape 4 : retour dans `main`, `a = make_numbers(n)`

    STACK
    main : a = 0xH ---+   b = NULL   n = 5
                      |
    HEAP              v
    bloc à 0xH : [0][11][22][33][44]

La frame de `make_numbers` est détruite : `arr`, `i` et son `n` n'existent
plus. Le bloc heap, lui, survit, car sa durée de vie ne dépend pas de la
fonction qui l'a créé mais du `free`. La responsabilité de le libérer passe à
`main`, via `a`. Les adresses du premier `printf` (a et b identiques)
confirment l'étape suivante.

### Étape 5 : `b = a` (aliasing)

    STACK
    main : a = 0xH ---+
           b = 0xH ---+--> bloc [0][11][22][33][44]

`a` et `b` sont deux variables distinctes sur la stack contenant la même
adresse : deux alias du même bloc. Sortie : `a=0x25df9420 b=0x25df9420`,
`a[2]=22 b[2]=22`. Un seul `free` suffit, et il doit être fait une seule fois.

### Étape 6 : `free(a)`

    STACK
    main : a = 0xH ---+
           b = 0xH ---+--> 0xH : mémoire rendue à l'allocateur,
                                 n'appartient plus au programme

`free` ne modifie ni `a` ni `b` : les deux contiennent toujours 0xH
(sortie : `b=0x25df9420`). Les deux sont des pointeurs pendants (dangling),
pas seulement `b`. La durée de vie du bloc va de `malloc` (dans
`make_numbers`) à `free(a)`.

### Étape 7 : utilisation de `b` après le free (use-after-free)

    Ligne 42 : b[2] lu    -> adresse 0xH + 8,  lecture de 4 octets
    Ligne 44 : b[3] écrit -> adresse 0xH + 12, écriture de 4 octets
    Ligne 45 : b[3] relu  -> adresse 0xH + 12, lecture de 4 octets

Résultat observé : `reading b[2]=-1781134091` alors que la valeur écrite
avant le free était 22. La mémoire a donc été modifiée par quelqu'un d'autre
après le `free(a)`. Le `free` n'a pas "effacé" le bloc : il l'a rendu à
l'allocateur, qui peut réutiliser ces octets pour ses propres données.
Explication probable (hypothèse à confirmer avec Valgrind, non vérifiée) : la
glibc stocke des informations de gestion dans les premiers octets d'un bloc
libéré, ce qui écraserait `b[2]`.

`wrote b[3]=1234` s'affiche normalement et le programme ne plante pas.
Cela ne prouve rien : c'est un comportement indéfini qui "fonctionne" ici par
chance. Une écriture dans un bloc libéré peut corrompre les données de
l'allocateur et provoquer un plantage plus tard, à un autre endroit du code.

### Étape 8 : `return 0`

Les variables de `main` (`a`, `b`, `n`) disparaissent avec sa frame.
Il n'y a pas de fuite mémoire : le bloc a été libéré. Le bug est un accès
invalide, pas un leak.

## Erreur de l'IA n°2 : le printf de la ligne 40

### Ce que l'IA a affirmé

Elle a écrit que `printf("after free(a): b=%p", (void *)b)` était
"inoffensif en pratique" parce qu'il n'accède pas à la mémoire pointée, il
affiche seulement la valeur de `b`.

### Pourquoi c'est faux ou trompeur

Lors de la compilation, GCC signale cette ligne exactement comme les lignes 42,
44 et 45 (`-Werror=use-after-free`). Le standard C indique que la valeur d'un
pointeur devient indéterminée après le `free` du bloc qu'il désigne : même
lire `b` sans le déréférencer est un comportement indéfini. Le résultat
affiché (`0x25df9420`) est "correct" ici, mais le compilateur est en droit
d'exploiter cette erreur.

### Correction

Ligne 40 classée comme comportement indéfini au même titre que les lignes
42 à 45, et non comme cas bénin. Bonne pratique : mettre `a = NULL` et
`b = NULL` juste après le `free`, car un pointeur `NULL` est détectable, alors
qu'un pointeur pendant ne l'est pas.

## Erreur de l'IA n°3 : dangling n'était pas limité à `b`

Le texte du programme dit "`b` (dangling)" et mon premier schéma pouvait le
laisser croire. En réalité `a` aussi est pendant après `free(a)` : il contient
toujours la même adresse (voir étape 6). C'est le propre de l'aliasing : libérer
via un alias invalide tous les autres.