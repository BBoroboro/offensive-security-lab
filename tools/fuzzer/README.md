to compile vuln1.c
cc -Wall -Werror -Wextra vuln1.c -o vuln1



cc -Wall -Werror -Wextra main.c -o fuzzer



ROADMAP:

- fuzzer must run vuln program

- must send input (now it doesnt work if the program uses fgets)
see execve + fork + dup2 + waitpid

- must recognizes if the program crashes

