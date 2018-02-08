#include "endian_swap.h"

/*
 * word should have been allocated memory of wordsize before running this function
 * return the number of bytes read.
 */
int readword(char* word, int wordsize) {
    int c, i;

    i = 0;
    /* EOF is always defined to be -1. */
    /* i byte (0 ~ 255) for each input, but need to expect -1 */
    while(i < wordsize) {
        if((c = getchar()) == -1)
            break;
        *word = c;
        word++;
        i++;
    }

    return i;
}

int endian_swap(int wordsize) {
    char* word;
    int byteread;
    int i;

    word = (char*)malloc(wordsize);

    /*  */
    while((byteread = readword(word, wordsize))) {
        /* when first char input was EOF */
        if(byteread == 0)
            break;

        /* if num of bytes read was smaller than word, */
        /* fill in the rest of the word with zeros */
        if(byteread < wordsize) {
            for(; byteread < wordsize; byteread++)
                word[byteread] = 0;
        }

        /* swap the word (just print it out inverse order) */
        for(i = wordsize-1; i >= 0; i--)
            putchar(word[i]);
    }

    free(word);
    return 1;
}