// primes.c
// Řešení IJC-DU1, příklad a), 21.3.2022
// Autor: Matej Sirovatka, FIT
// Přeloženo: gcc 10.2.1 20210110
// Zdrojový soubor pro hledáni prvočísel

#include "bitset.h"
#include <stdio.h>
#include <time.h>
#include "eratosthenes.h"

#define SIZE 300000000

int main(){
	//start clock
	clock_t start = clock();
	
	bitset_create(arr, SIZE);

	//array for last 10 primes
	int final_primes[10] = {0};
	Eratosthenes(arr);
	int idx = 0;

	//iterate bitset from the end and save gotten prime numbers
	for (unsigned long i = SIZE - 1; i > 0; i--) {
		if (bitset_getbit(arr, i) == 0){
			final_primes[idx] = i;
			idx++;

			//break when enough primes found
			if (idx == 10) {
				break;
			}
		}
	}

	//print the primes 
	for (int i = 10; i > 0; i--) {
		printf("%d\n", final_primes[i-1]);
	}
	
	//print the time
	fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

	return 0;
}
