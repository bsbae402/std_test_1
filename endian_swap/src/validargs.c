#include "validargs.h"

bool help_option = false;

bool is_uint(char* str) {
    for( ; *str != '\0'; str++) {
        if(!isdigit(*str))
            return false;
    }
    return true;
}

int atoi(char* s) {
    int i, n;
    n = 0;
    for(i=0; s[i] >= '0' && s[i] <= '9'; i++) {
        n = 10*n + (s[i] - '0');
    }
    return n;
}

/**
 * @brief
 * @details
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return 1 if valid, 0 if invalid
 * @modifies global variable "global_options"
 */
int validargs(int argc, char **argv)
{
    if(argc != 3) {
        return 0;
    }

    for(--argc, ++argv; argc > 0; argc--, argv++) {
        char *arg = *argv;

        if(*arg != '-')
            return 0;

        switch(*++arg) {
            case 'h':
                help_option = true;
                return 1;
            case 'w': ////
                if(--argc <= 0)
                    return 0;

                if(is_uint(*++argv))
                    wordsize = atoi(*argv);
                else
                    return 0;
                break;
            default:
                return 0;
        }
    }
    return 1;
}
