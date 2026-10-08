#include "fuzzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void    save_crach(t_seed seed) { // not correct name
    // char *str = input->input; //change
    FILE *file;
    file = fopen("crash_res", "w"); // check if failed
    // fprintf(file)
    fputs("crahed!\n", file);
    fwrite(seed.input, 1, seed.size, file);
    fputs("\n------------\n", file);
    fclose(file);
}

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
                    save_crach(seed_copy); // correct later
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
