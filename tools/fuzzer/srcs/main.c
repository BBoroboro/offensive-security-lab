#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "fuzzer.h"

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
            if (errno || *end || end == arg || a->iterations < 1 || a->iterations > 1000)
                argp_error(state, "--iterations must be a number between 1 and 1000");
            break;
        case 'i':
            // printf("input file is %s\n", arg);
            a->input_file = arg;
            break;
        case 's': // change to accept binary stdin
            a->seed.input = (unsigned char *)arg; //change 
            a->seed.size = strlen(arg); // change
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

int main(int ac, char** av, char** envp) {
    t_config    config = {0};
    t_process   process;
    srand(time(NULL));
    if (!config.timeout)
        config.timeout = TIMEOUT; // change later, add flag

    struct argp_option options[] = { // add timeout?? 
        { "target", 't', "FILE", 0, "file to target", 0 }, // change later
        { "iterations", 'n', "N", 0, "number of iterations per seed", 0},
        { "input_file", 'i', "FILE", 0, "file containing multiple seeds\\inputs", 0},
        { "seed", 's', "SEED", 0, "supply one seed", 0},
        { 0 }
    };

    struct argp argp = { options, parse_opt, 0, "Mandatory flags: -t, -n, -i or -s", 0, 0, 0 };
    argp_parse(&argp, ac, av, 0, 0, &config);
    
    memset(&process, 0, sizeof(t_process));


    check_file(config.target); // put in parse opt??
    if (config.input_file != NULL) {
        process_corpus_input(&config, &process, envp);
    }
    else
        ft_process(&process, &config, envp);

    // ft_free_all(&data, &input);
    return 0; 
}