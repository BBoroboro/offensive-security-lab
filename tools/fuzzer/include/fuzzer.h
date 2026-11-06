#ifndef FUZZER_H
# define FUZZER_H

# define READ 0
# define WRITE 1
# define TIMEOUT 1

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
    unsigned char       *input; // change to data?
    size_t     size;
}   t_seed;

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
    FILE    *seed_file; // remove, pretty useless after all, no need to keep it after reading
    int     status;
    int     crash;
    char    *input_list; // not used
    size_t  list_size;
    int     interation; // to check which process crash or an id?
}   t_process;


void     check_file(char *filename);

// pipe.c
void    open_pipes(t_process *process);
// void    close_pipe(t_data *data);

// process.c
void    parent_process(t_process *process, t_config *config, t_seed seed_copy);
void    child_process(t_process *process, t_config *config, char **envp);
int    ft_process(t_process *process, t_config *config, char **envp);
void    process_list_input(t_config *config, t_process *process, char **envp);

// free.c
// void    ft_free_all(t_data *data, t_input *input);

//error.c
// void    error_init(t_data *data, t_input *input, char *msg_err);


#endif