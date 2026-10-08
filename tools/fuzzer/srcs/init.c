#include "fuzzer.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// int    init_input(t_input *input, t_data *data, char *filename, char *str) {

// int     init_seed(t_data *data, t_input *input, char *seed) {
//     input->input = malloc(strlen(seed) + 1);
//     if (input->input == NULL) {
//         error_init(data, input, "Input memory allocation failed\n");
//         // fprintf(stderr, "Input memory allocation failed\n");
//         // return 1;
//     }
//     strcpy(input->input, seed); //use a safer method?
//     input->size = strlen(seed);
//     input->input[input->size] = '\0';
//     return 0;
// }

// int    create_seed(t_data *data, t_input *input) {
//     char *str = "Hello!\n";

//     if (input->input != NULL)
//         free(input->input);
//         // return 0;
//     input->input = malloc(strlen(str) + 1);
//     if (input->input == NULL) {
//         error_init(data, input, "Input memory allocation failed\n");
//         // fprintf(stderr, "Input memory allocation failed\n");
//         // return 1;
//     }
//     strcpy(input->input, str); //use a safer method?
//     input->size = strlen(str);
//     input->input[input->size] = '\0';
//     return 0;
// }

// int     init_target(t_data *data, t_input *input, char *target) {
//     data->filename = malloc(strlen(target) + 1);
//     if (data->filename == NULL) {
//         error_init(data, input, "Filename memory allocation failed\n");
//         // fprintf(stderr, "Filename memory allocation failed\n");
//         // return 1;
//     }
//     strcpy(data->filename, target); //use a safer method?
//     return 0;
// }

// int     is_num(char *str) {
//     for (size_t i = 0; i < strlen(str); i++) {
//         if (isdigit(str[i]) == 0) {
//             // printf("%c it not digit\n",str[i] ); // test
//             return 1;
//         }
//     }
//     return 0;
// }

// int     init_iteration(t_data *data, t_input *input, char *it) {
//     if (is_num(it)) {
//         error_init(data, input, "Iteration is not a number\n"); // change later
//         // return 1;
//     }
//     data->iteration = atoi(it);
//     return 0;
// }

// int    init_input(t_input *input, t_data *data, char **args) {

//     //control input here, put check file, check if seed and control, check if iteration and control

//     if (args[2] != NULL)
//         init_seed(data, input, args[2]);
//     else
//         create_seed(data, input);
//     init_target(data, input, args[1]);
//     if (args[3] != NULL && args[3] != 0) {
//         init_iteration(data, input, args[3]); // error pas gerer
//     }
//     return 0;
// }

