#include "fuzzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void    print_header(FILE *file) {
    fputs("\t\t\t\t####################################\n", file);
    fputs("\t\t\t\t#    The target program crahed!    #\n", file);
    fputs("\t\t\t\t####################################\n\n\n", file);
}

void    save_crach(t_process *process, t_seed seed) { // not correct name
    FILE *file;

    if (process->crash == 0) {
        file = fopen("crash_res", "w"); // check if failed
        // fputs("The target program crahed!\n", file);
        print_header(file);
    }
    else
        file = fopen("crash_res", "a"); // check if failed
    process->crash++;


    fputs("\n\n=========================\n\n", file);
    fprintf(file, "CRASH N° %d :\n\n", process->crash);
    fputs("SEED: ---", file);
    fwrite(seed.input, 1, seed.size, file);
    fputs("---\n\n", file);
    fputs("SEED LENGTH: ", file);
    fprintf(file, "%ld", seed.size); 
    fputs("\n\n=========================\n\n", file);
    fclose(file);
}

// void    save_crach(t_seed seed) { // not correct name
//     FILE *file;

//     file = fopen("crash_1", "w"); // check if failed
//     fputs("The target program crahed!\n", file);
//     fputs("Input: ---", file);
//     fwrite(seed.input, 1, seed.size, file);
//     fputs("---\n", file);
//     fputs("Length: ", file);
//     fprintf(file, "%ld", seed.size);
//     fputs("\n------------\n", file);
//     fclose(file);
// }

void    child_process(t_process *process, t_config *config, char **envp) { 
        dup2(process->fds[0], STDIN_FILENO); // check error
        close(process->fds[0]);
        close(process->fds[1]);

        char *args[] = {config->target, NULL};
        execve(args[0], args, envp);

        perror("execve");
        exit(1);
}

void    parent_process(t_process *process, t_config *config, t_seed seed_copy) {
        close(process->fds[0]);
        write(process->fds[1], seed_copy.input, seed_copy.size);
        close(process->fds[1]);

        time_t start = time(NULL);
        time_t end = start + config->timeout;
        int w;

        while(1) {
            w = waitpid(process->pid, &process->status, WNOHANG);
            if (w < 0) {
                perror("wait() error");
            }
            if (w == process->pid) {
                if (WIFEXITED(process->status))
                    printf("exit status: %d\n", WEXITSTATUS(process->status)); // test
                if (WIFSIGNALED(process->status)) {
                    printf("signal: %d\n", WTERMSIG(process->status)); // test
                    save_crach(process, seed_copy);
                    // save_crach(seed_copy); // correct later
                }
                break;
            }
            if (w == 0) {
                time_t current = time(NULL);
                if (current >= end) {
                    kill(process->pid, SIGKILL);
                    waitpid(process->pid, &process->status, 0);
                    break;
                }
                // sleep(1); // optimize
            }
        }
}
