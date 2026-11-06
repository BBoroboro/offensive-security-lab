#include "fuzzer.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void    mutate_seed(t_seed seed) { //do not mutate size yet
    int index;
    index = 0;
    index = rand() % seed.size;
    seed.input[index] = rand() % 256;
}

int  copy_seed(t_seed *seed_copy, t_config *config) {
    seed_copy->size = config->seed.size;
    seed_copy->input = malloc(seed_copy->size ? seed_copy->size : 1);
    if (!seed_copy->input) 
        return 1; // change later
    memcpy(seed_copy->input, config->seed.input, seed_copy->size);
    return 0;
}


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

int    ft_process(t_process *process, t_config *config, char **envp) {
    for (int i = 0; i < config->iterations; i++) {
        t_seed seed_copy;
        if (copy_seed(&seed_copy, config))
            return 1; // error msg

        if (i >= 1) {
            mutate_seed(seed_copy);
        }

        open_pipes(process);
        process->pid = fork();
        if (process->pid == -1) { // clean better what if we are in the middle of the process
            perror("fork"); 
            return 1;
        }
        if (process->pid == 0) {
            child_process(process, config, envp);
        }
        else {
            parent_process(process, config, seed_copy);
        }
        // if(mutated_seed != NULL)
        free(seed_copy.input);
        seed_copy.input = NULL;
    }
    return 0;
}

void    process_list_input(t_config *config, t_process *process, char **envp) {
        char    *line;
        size_t  capacity;
        ssize_t nread;

        check_file(config->input_file);
        process->seed_file = fopen(config->input_file, "r"); // check i failed
        // process.seed_file = NULL;
        // if (!process.seed_file) {
        //     fprintf(stderr, "Failed to open file '%s'\n", config.input_file);
        //     exit(1);
        // }

        nread = 0;
        capacity = 0;
        line = NULL;
        // while((nread = getline(&config->seed.input, &process->list_size, process->seed_file)) != -1) {
        while((nread = getline(&line, &capacity, process->seed_file)) != -1) {
            // printf("seed is %s", config->seed.input);
            if (nread > 0 && line[nread - 1] == '\n')
                nread--;
            config->seed.input = (unsigned char *)line;
            config->seed.size = (size_t)nread;
            if (config->seed.size == 0)
                continue;
            ft_process(process, config, envp);
        }
        
        free(config->seed.input);
        fclose(process->seed_file);
}
