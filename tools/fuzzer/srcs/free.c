#include "fuzzer.h"

// void    ft_free_all(t_data *data, t_input *input) {
//     if (input->input)
//         free(input->input);
//     if (data->filename)
//         free(data->filename);
//     close_pipe(data);
//     // free(data);
//     // free(input);
// }