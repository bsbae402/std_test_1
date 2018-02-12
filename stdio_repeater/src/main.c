#include <stdlib.h>
#include <stdio.h>

#include "validargs.h"

int main(int argc, char **argv)
{
    char ch;

    while(1) {
        ch = getchar();
        if(ch != EOF)
            putchar(ch);
        else
            break;
    }

    return EXIT_SUCCESS;
}
