#include <stdlib.h>

#include "validargs.h"
#include "endian_swap.h"
#include "debug.h"

/*
    sizeof(unsigned int) = 4
    sizeof(unsigned short) = 2
    sizeof(char) = 1
    sizeof(short) = 2
    sizeof(int) = 4
    sizeof(long) = 8
    sizeof(long long) = 8
    sizeof(float) = 4
    sizeof(double) = 8
    sizeof(long double) = 16
*/
int main(int argc, char **argv)
{
    if(!validargs(argc, argv)) {
        USAGE(*argv, EXIT_FAILURE);
        return EXIT_FAILURE; //// <- do I need this?
    }

    if(help_option) {
        USAGE(*argv, EXIT_SUCCESS);
        // return EXIT_SUCCESS; //// <- don't need this because USAGE(?, EXIT_SUCCESS) will call exit()
    }

    // do swap
    endian_swap(wordsize);

    return EXIT_SUCCESS;
}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */
