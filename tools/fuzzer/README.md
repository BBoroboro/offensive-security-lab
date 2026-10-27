
# C Fuzzer

A lightweight, mutation-based fuzzer written in C to test program robustness against modified inputs and identify potential crashes.

## Features

- **Seed-based fuzzing:** Load multiple seeds from an input file or provide a single seed directly.
- **Mutation-based testing:** Apply random mutations to seeds across configurable iterations.
- **Process isolation:** Use `fork()` to execute the target in child processes.
- **Crash detection:** Monitor child process termination with `waitpid()` and record detected crashes.
- **Hang handling:** Handle executions that exceed the expected runtime.
- **Crash logging:** Save information about detected crashes for further analysis.

## Usage

- **make** to compile fuzzer
- **make vuln** to compile vulnerable programs in 'vuln_src'

```bash
./fuzzer --help
```

### Options

| Option | Description |
|---|---|
| `-t, --target=FILE` | Target program to test |
| `-i, --input_file=FILE` | File containing multiple seeds or inputs |
| `-s, --seed=SEED` | Provide a single seed |
| `-n, --iterations=N` | Number of iterations per seed |
| `-?, --help` | Display help |

**Required options:** `-t` and `-n`, plus either `-i` or `-s`.

### Examples

Run the fuzzer against a target using a single seed:

```bash
./fuzzer -t ./target -s "test" -n 100
```

Run the fuzzer using seeds stored in a file:

```bash
./fuzzer -t ./target -i seeds.txt -n 100
```

## How It Works

1. Load one or more initial seeds.
2. Generate mutated inputs using random mutations.
3. Execute the target in an isolated child process.
4. Monitor process termination and handle hangs.
5. Record detected crashes for further investigation.

## Current Limitations & fix

- Mutations do not currently change the size of the original seed.
- Mutation strategies are currently random rather than coverage-guided.
- Crash analysis and input minimization are not yet implemented.

### Fix
- seeds from .txt keep the ending '\n'
- need to fix all error checks (fopen, fork, etc) NOT SECURE FOR NOW


## Roadmap

- Add variable-length mutations, including insertion and deletion of bytes.
- Improve process management and execution monitoring.
- Enrich crash reports to facilitate reproduction and analysis.
- Explore more advanced mutation strategies.




<!-- 


###################


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

À terme, une fonctionnalité particulièrement intéressante serait la réduction d'une entrée qui provoque un crash afin d'obtenir un cas de test minimal. -->