#ifndef CONST_H
#define CONST_H

#include <stdio.h>

#define USAGE(program_name, retcode) do{ \
fprintf(stderr, "USAGE: %s %s\n", program_name, \
"-w WORDSIZE \n" \
"    -e       WORDSIZE specifies the size of word in byte (digit)\n" \
"    -h       Display this help menu."); \
exit(retcode); \
} while(0)

unsigned int wordsize;

#endif
