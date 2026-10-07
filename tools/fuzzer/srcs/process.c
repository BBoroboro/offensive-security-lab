#include "fuzzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void    save_crach(char *seed) { // not correct name
    // char *str = input->input; //change
    FILE *file;
    file = fopen("crash_1", "w"); // check if failed
    // fprintf(file)
    fputs("crahed!\n", file);
    fwrite(seed, 1, strlen(seed), file);
    fputs("\n------------\n", file);
    fclose(file);
}

// int    timeout_reached(t_data *data) { // NOT USED ANYMORE
//     time_t start = time(NULL);
//     // printf("START = %ld\n", start); // test
//     // printf("timeout is %d\n", data->timeout); //test
//     long int end = start + data->timeout;
//     // printf("end is %ld\n", end); //test

//     if (time(NULL) >= end)
//         return 1;
//     return 0;

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

void    parent_process(t_process *process, t_config *config, char *mutated_seed) {
        close(process->fds[0]); 
        if (mutated_seed == NULL)
            mutated_seed = config->seed;
        write(process->fds[1], mutated_seed, strlen(mutated_seed));
        close(process->fds[1]);

        time_t start = time(NULL);
        config->timeout = 1; // change later
        time_t end = start + config->timeout; // change later for better precision
        int w;

        while(1) {
            w = waitpid(process->pid, &process->status, WNOHANG);
            if (w == process->pid) {
                if (WIFEXITED(process->status))
                    printf("exit status: %d\n", WEXITSTATUS(process->status)); // test
                if (WIFSIGNALED(process->status)) {
                    printf("signal: %d\n", WTERMSIG(process->status)); // test
                    save_crach(mutated_seed); // correct later
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
        // mutate_seed(input);
}

