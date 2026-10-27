#include "fuzzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void     check_file(char *filename) {
    if (!access(filename, R_OK) == 0) {
        fprintf(stderr, "./fuzzer: missing destination file or not readable: '%s'\n", filename);
        fprintf(stderr, "Try './fuzzer --help' for more information.\n");
        exit (1);
    }
}
