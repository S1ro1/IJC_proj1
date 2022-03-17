#include "bitset.h"
#include "eratosthenes.h"
#include <stdio.h>
#include <time.h>

#define SIZE 300000000

int main(){
	clock_t start = clock();
	
	bitset_alloc(arr, SIZE);

	int final_primes[10] = {};
	Erathostenes(arr);
	int idx = 0;

	for (unsigned long i = SIZE - 1; i > 0; i--) {
		if (bitset_getbit(arr, i) == 0){
			final_primes[idx] = i;
			idx++;
		
			if (idx == 10) {
				break;
			}
		}
	}

	for (int i = 10; i > 0; i--) {
		printf("%ld\n", final_primes[i-1]);
	}
	
	fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

	bitset_free(arr);
	return 0;
}