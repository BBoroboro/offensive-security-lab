#include "fuzzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




void     check_file(char *filename) { // change
    if (access(filename, F_OK) == 0) {
        printf("File %s exits\n", filename); // change
    }
    else {
        fprintf(stderr, "./fuzzer: missing destination file operand after '%s'\n", filename);
        fprintf(stderr, "Try './fuzzer --help' for more information.\n");
        exit (1); // change? 
    }
    // check if readable ?
}

void    check_input() {
    
}