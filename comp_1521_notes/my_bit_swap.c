// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    int mask0 = 0b0101010101010101010101010101010101010101010101010101010101010101;
    int mask1 = mask0;
    mask1 <<= 1;

    int temp0 = (value & mask0);
    int temp1 = (value & mask1);

    temp0 <<= 1;
    temp1 >>= 1;

    return temp0 + temp1;
}
