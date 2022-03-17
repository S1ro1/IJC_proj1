#include "bitset.h"

#ifdef USE_INLINE

extern bitset_index_t bitset_size(bitset_t name);
extern void bitset_free(bitset_t name);
extern int bitset_getbit(bitset_t name, bitset_index_t idx);
extern void bitset_setbit(bitset_t name, bitset_index_t idx, int expr); 

#endif