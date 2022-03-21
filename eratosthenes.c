#include <math.h>
#include "eratosthenes.h" 
#include <stdio.h>

//Eratosthenes sieve implementation
void Eratosthenes(bitset_t arr){
	unsigned long size = bitset_size(arr);

	unsigned long range = sqrt(size);

	bitset_setbit(arr, 0, 1);
	bitset_setbit(arr, 1, 1);

	for (unsigned long i = 2; i < range; i++) {
		if (bitset_getbit(arr, i) == 0) {
			for (unsigned long j = i * i; j < size; j += i) {
				bitset_setbit(arr, j, 1);
			}
		}
	}
}