#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "error.h"
#include "eratosthenes.h"
#include "ppm.h"
#include "bitset.h"

#define MASK (char)1

int main(int argc, char *argv[]) {
    //check if only file was provided
    if (argc != 2) {
        error_exit("Wrong number of arguments was provided\n");
    }

    //read it into ppm struct
    struct ppm * img = ppm_read(argv[1]);

    if (!img) {
        error_exit("Error reading input file\n");
    }

    size_t length = img->xsize * img->ysize * 3;

    bitset_alloc(arr, length);

    //fill the bitset with eratosthenes
    Eratosthenes(arr);

    //checks how many bits were already found, at 8, char is printed
    int current_bit = 0;
    
    char c = '\0';

    for (size_t i = 29; i < length; i++) {
        if (bitset_getbit(arr, i) == 0) {
            //get the current data
            char current_data = img->data[i];

            //get the last bit of the data
            char bit_val = MASK & current_data;
            //shift it to a correct position
            bit_val = bit_val << current_bit;

            //set the correct position of char to 1 or 0, depending on the bit_val
            c |= bit_val;

            //another bit found
            current_bit++;

            //if this passes, then we filled a whole char that we can print out
            if (current_bit == CHAR_BIT) {
                putc(c, stdout);
                //check if char was '\0'
                if (c == '\0') {
                    //success
                    bitset_free(arr);
                    ppm_free(img);
                    return 0;
                }
                //reset the variables
                current_bit = 0;
                c = '\0';
            }

        } 
        
    }
    //no '\0' was found, so the message wasn't finished with '\0'
    bitset_free(arr);
    ppm_free(img);
    error_exit("No EOF detected\n");
}