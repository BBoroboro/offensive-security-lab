#include "fuzzer.h"

//multipiping later
void    open_pipes(t_process *process) {
    if (pipe(process->fds) == -1) {
        // ft_exit_error((data), "Pipe");  do later
    }
}

void    close_pipe(t_data *data) {

    if (data->fds[0])
        close(data->fds[0]);
    if (data->fds[1])
        close(data->fds[1]);
}