#include "max5494_max5499.h"

#include <stdio.h>

int main(void)
{
    int cnt = 0;

    if (cnt == 0)
    {
        printf("OK\n");
        return 0;
    }
    else
    {
        fprintf(stderr, "%d errors found.\n", cnt);
        return 1;
    }
}