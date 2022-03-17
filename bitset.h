#ifndef BITSET_1_H
#define BITSET_1_H

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "error.h"

typedef unsigned long *bitset_t;
typedef unsigned long bitset_index_t;

#define ul_bits (sizeof(unsigned long) * CHAR_BIT)

#define bitset_create(name, size)\
	static_assert(size > 0, "Size has to be over 0");\
	unsigned long name[(((size % ul_bits) > 0) ? (size / ul_bits + 2) : (size / ul_bits + 1))] = {size};\

#define bitset_alloc(name, size)\
	assert(size > 0);\
	bitset_t name = calloc((((size % ul_bits) > 0) ? (size / ul_bits + 2) : (size / ul_bits + 1)),\
	sizeof(unsigned long));\
	if (name == NULL) error_exit("bitset_alloc: Error allocating memory");\
	name[0] = size;\

#ifndef USE_INLINE

#define bitset_free(name) free(name)

#define bitset_size(name) name[0]

#define bitset_setbit(name, idx, expr)\
	(idx > name[0]) ? error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu",\
    (unsigned long)idx, (unsigned long)bitset_size(name)) : ((expr) ?\
	((name[(1 + idx / ul_bits)]) |=\
	(1ul << (idx % ul_bits))) :\
	((name[(1 + idx / ul_bits)]) &=\
	~(1ul << (idx % ul_bits))))

#define bitset_getbit(name, idx)\
	(idx >= name[0]) ?\
	(error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu",\
	(unsigned long)idx, (unsigned long)name[0])), 42 :\
	((name[(1 + idx / ul_bits)] &\
	(1ul << (idx % ul_bits))) != 0)

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


