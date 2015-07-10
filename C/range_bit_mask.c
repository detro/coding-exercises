#include <stdio.h>
#include <stdlib.h>

unsigned int range_bit_mask(unsigned int high_bit, unsigned int low_bit) {
    unsigned int right_mask = (0x1 << low_bit) - 1;
    unsigned int left_mask = 0xFFFFFFFF ^ ( (0x1 << high_bit + 1) - 1);
    
    return ((0xFFFFFFFF & ~right_mask) & ~left_mask);
}

int main(unsigned int argc, char** argv) {
    unsigned int h, l;
    if ( argc == 3 ) {
        h = atoi(argv[1]);
        l = atoi(argv[2]);
    } else
        return EXIT_FAILURE;
    
    printf("range_bit_mask(%d, %d) = 0x%08x\n", h, l, range_bit_mask(h, l));
    return EXIT_SUCCESS;
}