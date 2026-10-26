#include <stdio.h>
#include <string.h>

int main(int ac, char **av) {
    char input[100];
    char input2[100];

    (void)ac;
    (void)av;

    fgets(input, 100, stdin);
    
    if (strcmp(input, "crashme") == 0) 
    {
        printf("BOOM! Crash triggered.\n");
        *(int*)0 = 0;  // segmentation fault
    } else {
        printf("first input\n");
        printf("Safe input: %s\n", input);
    }
    
    fgets(input2, 100, stdin);
    if (strcmp(input2, "POPOL") == 0) {
        printf("BOOM! Crash triggered.\n");
        *(int*)0 = 0;  // segmentation fault
    } else {
        printf("second input\n");
        printf("Safe input: %s\n", input2);
    }

    return 0;
}