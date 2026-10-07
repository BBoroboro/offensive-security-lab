#include <stdio.h>
#include <string.h>

int main(int ac, char **av) {
    char input[100];

    (void)ac;
    (void)av;

    // printf("%s\n", av[0]);
    // printf("%s\n", av[1]);

    fgets(input, 100, stdin);

    if (strcmp(input, "crashme") == 0) {
    // if (strcmp(av[1], "crashme\n") == 0) {
        printf("BOOM! Crash triggered.\n");
        *(int*)0 = 0;  // segmentation fault
    } else {
        printf("Safe input: %s\n", input);
    }
    return 0;
}