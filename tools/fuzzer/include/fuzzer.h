#ifndef FUZZER_H
# define FUZZER_H

# define READ 0
# define WRITE 1

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <argp.h>
#include <ctype.h>
#include <argz.h>

typedef struct s_seed {
    char       *input; // change to data?
    size_t     size;
}   t_seed;

typedef struct s_data { //change t_data with t_process
    int     fds[2];
    char    *filename; //target better?
    char    **input_res; // not used
    int     status;
    int     timeout;
    int     crash;
    unsigned int iteration;
    pid_t pid;
}   t_data;

typedef struct s_config {
    char            *target; // or input_file
    int             iterations;
    int             timeout;
    t_seed          seed; // change to seed struct above?
    char            *input_file; // change to fd?
}   t_config;

typedef struct s_process {
    int     fds[2];
    pid_t   pid;
    int     status;
    int     crash;
    char    **input_res; // not used
    int     intereation; // to check which process crash or an id?
}   t_process;

//input_control.c
// int    init_input(t_input *input, t_data *data, char **args);
void     check_file(char *filename);

// pipe.c
void    open_pipes(t_process *process);
void    close_pipe(t_data *data);

// process.c
void    parent_process(t_process *process, t_config *config, t_seed seed_copy);
void    child_process(t_process *process, t_config *config, char **envp);

// free.c
// void    ft_free_all(t_data *data, t_input *input);

//error.c
// void    error_init(t_data *data, t_input *input, char *msg_err);


#endif