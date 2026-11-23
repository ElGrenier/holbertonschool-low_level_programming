# Crash report : crash_example.c

## 1. Description du crash

Le programme affiche `requesting n=0`, puis s'arrête sur le signal SIGSEGV à la
ligne 32 : `nums[0] = 42;`. Les `printf` des lignes 34 et suivantes ne
s'exécutent pas (la sortie s'arrête après `requesting n=0`).

Valgrind localise l'instruction fautive :

    Invalid write of size 4
       at 0x401235: main (crash_example.c:32)
     Address 0x0 is not stack'd, malloc'd or (recently) free'd

Interprétation : une écriture de 4 octets (`sizeof(int)`) a visé l'adresse
0x0, qui n'appartient ni à la stack, ni au heap, ni à un bloc récemment libéré.

## 2. Chaîne causale, du code à l'accès invalide

1. Ligne 25 : `int n = 0;`. La taille demandée est 0.
2. Ligne 30 : `nums = allocate_numbers(n);` appelle la fonction avec `n = 0`.
3. Ligne 9 : `if (n <= 0)` est vraie.
4. Ligne 10 : `return NULL;`. La fonction sort avant le `malloc` (ligne 12), qui
   n'est jamais appelé.
5. Retour dans `main` : `nums` reçoit la valeur NULL (adresse 0).
6. Aucun test de `nums` entre la ligne 30 et la ligne 32.
7. Ligne 32 : `nums[0] = 42` équivaut à `*(nums + 0) = 42`, c'est-à-dire une
   écriture de 4 octets à l'adresse 0x0.
8. L'adresse 0x0 ne correspond à aucune page mappée dans l'espace d'adressage
   du processus. Le processeur déclenche un défaut de page, le noyau ne trouve
   aucune région valide et envoie SIGSEGV au processus.
9. L'action par défaut de SIGSEGV est de terminer le processus (core dump).

## 3. Cause racine

Déréférencement d'un pointeur nul (NULL pointer dereference) en écriture.
La cause racine n'est pas le segfault, mais l'appel de la ligne 30 dont
`main` ne vérifie pas le résultat : `allocate_numbers` renvoie NULL
volontairement pour `n <= 0` (ligne 10), et `main` traite ce retour comme un
pointeur valide.

## 4. Pourquoi l'accès est invalide

- Catégorie : comportement indéfini (undefined behavior) du langage C. Le
  standard n'attribue aucun sens au déréférencement de NULL.
- Mémoire concernée : ni la stack, ni le heap.
  - La variable `nums` elle-même est sur la stack de `main` et est valide ;
    sa **valeur** est NULL.
  - L'adresse visée (0x0) n'est dans aucune zone allouée. Le heap n'est pas
    en cause : `malloc` n'a jamais été appelé par `allocate_numbers`, ce qui
    est cohérent avec le "1 allocs" du résumé Valgrind (voir plus bas).
- Pas un pointeur non initialisé : `nums` est initialisé à NULL ligne 24.
  Un pointeur non initialisé contiendrait une valeur indéterminée et
  Valgrind afficherait une erreur différente (`--track-origins` n'a rien
  tracé ici).
- Le crash est reproductible parce que `n` est une constante dans le code :
  chaque exécution suit le même chemin. Le SIGSEGV lui-même vient de la
  configuration usuelle de Linux (adresses basses non mappées) : le standard
  C ne le garantit pas.

## 5. Autres informations de la sortie Valgrind

- `still reachable: 1,024 bytes in 1 blocks` et `1 allocs, 0 frees` : ce bloc
  n'est pas une fuite de mon code. `allocate_numbers` n'a rien alloué
  (retour ligne 10), et le programme ne contient aucun `malloc` exécuté. Il
  s'agit probablement du tampon de sortie de `printf` alloué par la
  bibliothèque C (hypothèse non vérifiée, cohérente avec les 1 024 octets
  vus dans `heap_example`). Le processus a été tué par le signal avant toute
  libération.
- Le message "stack overflow ... --main-stacksize" de Valgrind est un texte
  générique affiché pour tout SIGSEGV : il n'indique pas ici un dépassement de
  pile.

## 6. Critique des explications proposées par l'IA

| Hypothèse proposée | Verdict | Justification |
|---|---|---|
| Déréférencement de NULL à la ligne 32 | Correcte | Valgrind : écriture de 4 octets à l'adresse 0x0, ligne 32. |
| `malloc` a échoué (mémoire insuffisante) | Incorrecte | `malloc` n'est jamais appelé : le `return NULL` de la ligne 10 précède la ligne 12. |
| Stack overflow | Incorrecte | L'adresse fautive est 0x0, loin de la stack. Il n'y a ni récursion ni gros tableau local. Le texte de Valgrind est générique. |
| Dépassement de tableau (out-of-bounds) | Incorrecte | Il n'y a pas de tableau alloué ; l'indice 0 serait valide dans un tableau de taille >= 1. Le problème est l'absence de tableau, pas un indice. |
| Pointeur non initialisé | Incorrecte | `nums` est initialisé à NULL (ligne 24). NULL et valeur indéterminée sont deux erreurs différentes. |
| Fuite mémoire (les 1 024 octets) | Trompeuse | Le bloc est "still reachable" et ne provient pas des allocations du code. Il n'est pas la cause du crash. |

## 7. Correctif suggéré (optionnel, non appliqué)

Suggestion : vérifier le retour de `allocate_numbers` avant tout accès.

    nums = allocate_numbers(n);
    if (nums == NULL)
        return 1;

Alternative : valider `n` avant l'appel. Dans les deux cas, la fonction a deux
cas d'échec (`n <= 0` et `malloc` qui échoue) qui renvoient NULL, et l'appelant
doit traiter ce retour. Modifier `allocate_numbers` pour qu'elle appelle
`malloc(0)` n'est pas une bonne solution : le résultat de `malloc(0)` dépend
de l'implémentation (NULL ou pointeur non déréférençable).