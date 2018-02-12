#ifndef VALIDARGS_H
#define VALIDARGS_H

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

bool is_uint(char* str);
//int atoi(char* s);
int validargs(int argc, char **argv);

#endif
