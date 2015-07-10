#include <stdio.h>

unsigned int bits_counter_v0(unsigned int x) {
    unsigned int count = 0;
    while ( x != 0 ) {
        // If odd, add 1
        count += (x % 2 == 0) ? 0 : 1;
        x >>= 1;
    }
    
    return count;
}

unsigned int bits_counter_v1(unsigned int x) {
    unsigned int count = 0;
    while ( x != 0 ) {
        // If least-significant bit is 1, add 1
        count += (x & 1) ? 1 : 0;
        x >>= 1;
    }
    
    return count;
}

unsigned int bits_counter_v2(unsigned int x) {
    unsigned int count = 0;
    // "Hashmap" of the values for least significant 4 bits
    unsigned int int_to_bits_count[16] = {
        0, 1, 1, 2, // 0=00, 1=01, 2=10, 3=11
        1, 2, 2, 3, // 4=100, 5=101, 6=110, 7=111
        1, 2, 2, 3, // 8=1000, 9=1001, 10=1010, 11=1011
        2, 3, 3, 4  // 12=1100, 13=1101, 14=1110, 15=1111
    };
    
    while ( x != 0 ) {
        // Add the bits count of least significant 4 bits
        count += int_to_bits_count[ x & 15 ];
        x >>= 4;
    }
    
    return count;
}

unsigned int bits_counter_v3(unsigned int x) {
    unsigned int result = 0;
    // strip one set bit per iteration
    while (x != 0) {
        x &= x - 1;
        result++;
    }
    return result;
}

// Counting bits set in Parallel
unsigned int bits_counter_v4(unsigned int x) {
    // count bits of each 2-bit chunk
    x  = x - ((x >> 1) & 0x55555555);
    // count bits of each 4-bit chunk
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    // count bits of each 8-bit chunk
    x = x + (x >> 4);
    // mask out junk
    x &= 0xF0F0F0F;
    // add all four 8-bit chunks
    return (x * 0x01010101) >> 24;
}

int main(int argc, char** argv)
{
    int input;
    
    // Check the Input
	if ( argc == 2 ) input = atoi(argv[1]); else return (1);
	
	printf("--- BITS COUNTER METHODS ---\n");
	printf("bits_counter_v0(%d) = %d\n", input, bits_counter_v0((unsigned int)input));
	
	printf("bits_counter_v1(%d) = %d\n", input, bits_counter_v1((unsigned int)input));
	
	printf("bits_counter_v2(%d) = %d\n", input, bits_counter_v2((unsigned int)input));
	
    printf("bits_counter_v3(%d) = %d\n", input, bits_counter_v3((unsigned int)input));
    
    printf("bits_counter_v4(%d) = %d\n", input, bits_counter_v4((unsigned int)input));
	printf("----------------------------\n\n");
	
	return (0);
}