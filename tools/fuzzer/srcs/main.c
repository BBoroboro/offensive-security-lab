#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "fuzzer.h"

void    mutate_seed(t_seed seed) { //do not mutate size yet
    int index;
    index = 0;
    // printf("seed input is %s\n", seed.input); // test
    index = rand() % seed.size;
    seed.input[index] = rand() % 256;

    // printf("%s\n", mutated_seed); // test
}

static int parse_opt(int key, char *arg, struct argp_state *state) {
    t_config *a = state->input; 
    char *end;

    switch(key) {
        case 't':
            a->target = arg;
            break;
        case 'n':
            // check input between 1 to 1000 or 10000 as starter
            errno = 0;
            a->iterations = strtoul(arg, &end, 10);
            // printf("%ld\n", a->iterations);
            if (errno || *end || end == arg || a->iterations < 1 || a->iterations > 10000)
                argp_error(state, "--iterations must be a number between 1 and 10000");
            break;
        case 'i':
            // printf("input file is %s\n", arg);
            a->input_file = arg;
            break;
        case 's':
            // printf("seed is %s\n", arg);
            a->seed.input = arg;
            a->seed.size = strlen(arg);
            break;
        case ARGP_KEY_ARG:
            argp_error(state, "unexpected argument '%s'", arg);
            break;
        case ARGP_KEY_END: 
            if (!a->target || !a->iterations)
                argp_error(state, "--target and --iterations are required");
            if (!a->seed.input && !a->input_file)
                argp_error(state, "--seed or --input file (corpus) are required");
            if (a->seed.input && a->input_file)
                argp_error(state, "--choose a seed or an input file (corpus)");
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    } 
    return 0;
}

int  copy_seed(t_seed *seed_copy, t_config *config) {
    seed_copy->size = config->seed.size;
    seed_copy->input = malloc(seed_copy->size ? seed_copy->size : 1);
    if (!seed_copy->input) 
        return 1; // change later
    memcpy(seed_copy->input, config->seed.input, sizeof(seed_copy->size));
    return 0;
}

int    ft_process(t_process *process, t_config *config, char **envp) {
    for (int i = 0; i < config->iterations; i++) {
        t_seed seed_copy;
        if (copy_seed(&seed_copy, config))
            return 1; // error msg

        if (i >= 1) {
            mutate_seed(seed_copy);
            // printf("seed is %s\n", config->seed.input); // test 
            // printf("mutated seed is %s\n", seed_copy.input); // test
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


int main(int ac, char** av, char** envp) {
    t_config    config = {0};
    t_process   process; 
    srand(time(NULL));
    config.timeout = 1; // change later

    struct argp_option options[] = { // add timeout?? 
        { "target", 't', "FILE", 0, "file to target", 0 }, // change later
        { "iterations", 'n', "N", 0, "number of iterations per seed", 0},
        { "input_file", 'i', "FILE", 0, "file containing multiple seeds\\inputs", 0},
        { "seed", 's', "SEED", 0, "supply one seed", 0},
        { 0 }
    };

    struct argp argp = { options, parse_opt, 0, "Mandatory flags: -t, -n, -i or -s", 0, 0, 0 };

    argp_parse(&argp, ac, av, 0, 0, &config);

    check_file(config.target); // put in parse opt??
    memset(&process, 0, sizeof(t_process)); 

    ft_process(&process, &config, envp);

    // ft_free_all(&data, &input);

    return 0; 
}