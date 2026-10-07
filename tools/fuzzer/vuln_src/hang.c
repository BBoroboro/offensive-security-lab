#include <stdio.h>

int main(void)
{
    printf("Waiting forever...\n");
    // fflush(stdout);

    while (1)
        ;

    return 0;
}