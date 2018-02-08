#ifndef ENDIAN_SWAP_H
#define ENDIAN_SWAP_H

#include <stdio.h>
#include <stdlib.h>

int readword(char* word, int wordsize);

/*
 * STDIN until EOF; STDOUT the swap result
 */
int endian_swap(int wordsize);

#endif
