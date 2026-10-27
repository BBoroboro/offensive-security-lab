to compile vuln1.c
cc -Wall -Werror -Wextra vuln1.c -o vuln1



cc -Wall -Werror -Wextra main.c -o fuzzer



ROADMAP:

- fuzzer must run vuln program

- must send input (now it doesnt work if the program uses fgets)
see execve + fork + dup2 + waitpid

- must recognizes if the program crashes


TO SEND DIFFERENT INPUTS:
 $'hello\nPOPOL'


 Priorité 1 — Fiabiliser la détection des crashs

Si ce n'est pas déjà fait, vérifie le statut de terminaison de chaque processus enfant avec waitpid() et distingue :
- une terminaison normale ;
- une terminaison par signal, par exemple SIGSEGV ou SIGABRT ;
- une erreur de lancement ou d'exécution du programme cible.
Attention : tous les crashs ne produisent pas nécessairement le même signal, et un code de retour non nul ne signifie pas forcément que le programme a crashé.

Priorité 2 — Faire varier la taille des entrées

C'est une bonne évolution. Des mutations qui conservent toujours la taille initiale peuvent manquer certains bugs liés aux longueurs, aux limites de buffers ou au traitement de chaînes terminées par zéro.

Tu pourrais introduire des opérations d'insertion, de suppression et de duplication de segments d'octets, avec des limites configurables pour éviter des entrées démesurées.

Priorité 3 — Améliorer la qualité des mutations

rand() est suffisant pour un premier prototype. Ensuite, tu pourrais expérimenter des mutations plus structurées :
- inversion de bits et modification d'octets ;
- insertion ou suppression d'octets ;
- répétition de motifs ;
- mutations guidées par des dictionnaires de valeurs intéressantes.
L'objectif n'est pas d'accumuler les fonctionnalités, mais d'explorer des stratégies qui permettent de trouver des bugs différents.

Priorité 4 — Améliorer la gestion des processus et les résultats

Pense notamment aux timeouts pour les programmes qui se bloquent, à la gestion propre des processus enfants et à la conservation des entrées qui provoquent un crash. Pour chaque crash, enregistrer la seed mutée, le signal et quelques métadonnées facilitera la reproduction du problème.

À terme, une fonctionnalité particulièrement intéressante serait la réduction d'une entrée qui provoque un crash afin d'obtenir un cas de test minimal.