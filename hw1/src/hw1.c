#include "hw1.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

/*
 * You may modify this file and/or move the functions contained here
 * to other source files (except for main.c) as you wish.
 */

// TODO: Should I require an error if this argument doesn't meet
// format requirements?
static unsigned int parse_hex(char *s) {
    int ret = 0;
    while(*s != '\0') {
        ret *= 16;
        if(*s >= '0' && *s < '9')
            ret += *s - '0';
        else if(*s >= 'a' && *s <= 'f')
            ret += *s - 'a' + 10;
        else if(*s >= 'A' && *s <= 'F')
            ret += *s - 'A' + 10;
        else
            ; //TODO: error!
        s++;
    }
    return ret;
}

/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the
 * program, returning 1 if validation succeeds and 0 if validation fails.
 * Upon successful return, the selected program options will be set in the
 * global variable "global_options", where they will be accessible
 * elsewhere in the program.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return 1 if validation succeeds and 0 if validation fails.
 * Refer to the homework document for the effects of this function on
 * global variables.
 * @modifies global variable "global_options" to contain a bitmap representing
 * the selected options.
 */
int validargs(int argc, char **argv)
{

    int assemble = 0, disassemble = 0;
    int bigendian = 0;
    unsigned int baseaddr;
    unsigned int options = 0;

    for(--argc, ++argv; argc > 0; argc--, argv++) {
        char *arg = *argv;
        char c;

        if(*arg != '-')
            return 0;

        switch(*++arg) {
            case 'h':
                //// -- I think if -a or -d has already met, -h should be considered invalid
                if(disassemble || assemble)
                    return 0;
                //// --//
                options |= HELP_MODE;
                /* modif: set global_options */
                global_options = options; ////
                return 1;
            case 'a':
                if(disassemble)
                    return 0;
                assemble++;
                break;
            case 'd':
                if(assemble)
                    return 0;
                disassemble++;
                break;
            case 'e':
                if(!(assemble || disassemble))
                    return 0;
                if(--argc <= 0)
                    return 0;
                argv++;
                c = *argv[0];
                if(*argv[1] != '\0')
                    ; // TODO: error
                if(c == 'b')
                    bigendian++;
                else if(c != 'l')
                    ; // TODO: error
                break;
            case 'b':
                if(!(assemble || disassemble))
                    return 0;
                if(--argc <= 0)
                    return 0;
                baseaddr = parse_hex(*++argv);
                options |= baseaddr & BASE_ADDR_MASK;
                break;
            default:
                return 0;
        }
    }

    if((assemble && disassemble) || !(assemble || disassemble))
        return 0;
    if(disassemble)
        options |= DISASSEMBLE_MODE;
    if(bigendian)
        options |= BIG_ENDIAN_MODE;
    global_options = options;
    return 1;
}
