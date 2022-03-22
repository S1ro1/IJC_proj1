// bitset.h
// Řešení IJC-DU1, příklad a), 21.3.2022
// Autor: Matej Sirovatka, FIT
// Přeloženo: gcc 10.2.1 20210110
// Hlavičkový soubor na implementaci bitsetu

#ifndef BITSET_1_H
#define BITSET_1_H

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"

//to pass bitset to a function as pointer
typedef unsigned long *bitset_t;
//type of bitset index
typedef unsigned long bitset_index_t;

//number of bits in 1 unsigned long
#define ul_bits (sizeof(unsigned long) * CHAR_BIT)

//creates static bitset and fills it with 0s
#define bitset_create(name, size)\
	static_assert(size > 0, "Size has to be over 0");\
	unsigned long name[(((size % ul_bits) > 0) ? (size / ul_bits + 2) : (size / ul_bits + 1))] = {size};\

//allocates local bitset and fills it with 0s
#define bitset_alloc(name, size)\
	assert(size > 0);\
	bitset_t name = calloc((((size % ul_bits) > 0) ? (size / ul_bits + 2) : (size / ul_bits + 1)),\
	sizeof(unsigned long));\
	if (name == NULL) error_exit("bitset_alloc: Error allocating memory");\
	name[0] = size;\

//if inline funcs shouldn't be used
#ifndef USE_INLINE

//frees the bitset
#define bitset_free(name) free(name)

//returns the size of a bitset
#define bitset_size(name) name[0]

//sets the bit with index idx to a 1 if expr != 0, else sets it to 0
#define bitset_setbit(name, idx, expr)\
	(idx >= name[0]) ? error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",\
    (unsigned long)idx, (unsigned long)bitset_size(name)), 42 : ((expr) ?\
	((name[(1 + idx / ul_bits)]) |=\
	(1ul << (idx % ul_bits))) :\
	((name[(1 + idx / ul_bits)]) &=\
	~(1ul << (idx % ul_bits))))

//returns the value of the bit with index idx
#define bitset_getbit(name, idx)\
	(idx >= name[0]) ?\
	(error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",\
	(unsigned long)idx, (unsigned long)name[0])), 42 : /* 42 is answer to the universe*/\
	((name[(1 + idx / ul_bits)] &\
	(1ul << (idx % ul_bits))) != 0)

/*if this passes, no macros are defined, 
but theirs equivalents in inline functions (except bitset_alloc and bitset_create)*/
#else

inline bitset_index_t bitset_size(bitset_t name) {
	return name[0];
}

inline void bitset_free(bitset_t name) {
	free(name);
}

inline int bitset_getbit(bitset_t name, bitset_index_t idx) {
	if (idx >= bitset_size(name)) {
		error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",
		(unsigned long)idx, (unsigned long)bitset_size(name));
	}

	return ((name[1 + idx / ul_bits] & (1ul << (idx % ul_bits))) != 0);
}

inline void bitset_setbit(bitset_t name, bitset_index_t idx, int expr) {
	if (idx >= bitset_size(name)) {
		error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",
		(unsigned long)idx, (unsigned long)bitset_size(name));
	}

	if (expr) {
		name[1 + idx / ul_bits] |= (1ul << (idx % ul_bits));
	} else {
		name[1 + idx / ul_bits] &= ~(1ul << (idx % ul_bits));
	}
}

#endif
#endif


