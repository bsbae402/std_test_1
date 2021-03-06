#include <stdlib.h>

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

#include "hw1.h"
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

    debug("Options: 0x%X", global_options);

    if(global_options & HELP_MODE) {
        USAGE(*argv, EXIT_SUCCESS);
        // return EXIT_SUCCESS; //// <- don't need this because USAGE(?, EXIT_SUCCESS) will call exit()
    }

    if(global_options & DISASSEMBLE_MODE)
        disassemble();
    else
        assemble();

    return EXIT_SUCCESS;
}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */
