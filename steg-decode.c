#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "error.h"
#include "eratosthenes.h"
#include "ppm.h"
#include "bitset.h"

#define MASK (char)1

int main(int argc, char *argv[]) { 
    if (argc != 2) {
        error_exit("Wrong number of arguments was provided\n");
    }

    struct ppm * img = ppm_read(argv[1]);

    if (!img) {
        error_exit("Error reading input file\n");
    }

    size_t length = img->xsize * img->ysize * 3;

    bitset_alloc(arr, length);

    Eratosthenes(arr);

    int current_bit = 0;
    
    char c = '\0';

    for (size_t i = 29; i < length; i++) {
        if (bitset_getbit(arr, i) == 0) {
            char current_data = img->data[i];

            char bit_val = MASK & current_data;
            bit_val = bit_val << current_bit;

            c |= bit_val;

            current_bit++;

            if (current_bit == CHAR_BIT) {
                putc(c, stdout);
                if (c == '\0') {
                    bitset_free(arr);
                    ppm_free(img);
                    return 0;
                }
                current_bit = 0;
                c = '\0';
            }

        } 
        
    }
    bitset_free(arr);
    ppm_free(img);
    error_exit("No EOF detected\n");
}