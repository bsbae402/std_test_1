#ifndef VALIDARGS_H
#define VALIDARGS_H

#include <stdbool.h>
#include <ctype.h>
#include "const.h"
#include "validargs.h"

extern bool help_option;

bool is_uint(char* str);
int validargs(int argc, char **argv);

#endif
