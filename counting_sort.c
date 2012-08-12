#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void print_array(u_int *input, u_int ilen) {
    u_int i;

    printf("[ ");
    for (i = 0; i < ilen; ++i) {
        printf("%u ", input[i]);
    }
    printf("]\n");
}

u_int find_max(u_int *input, u_int ilen) {
    // NOTE: Assuming that at least 1 item can be found in 'input'
    u_int max = input[0],
        i;

    for (i = 1; i < ilen; ++i) {
        if (input[i] > max) {
            max = input[i];
        }
    }

    return max;
}

// Counting Sort (see http://en.wikipedia.org/wiki/Counting_sort)
u_int *counting_sort(u_int *input, u_int ilen) {
    u_int max_input = find_max(input, ilen),
        *count = (u_int*)malloc((max_input+1) * sizeof(u_int)),
        *output = (u_int*)malloc(ilen * sizeof(u_int)),
        i,
        total_positioned = 0,
        c_i;

    printf("MAX VALUE IN INPUT: %u\n\n", max_input);

    // Count how many times the element at "input[i]" appears in "input"
    for (i = 0; i < ilen; ++i) {
        ++count[input[i]];
    }

    // Calculate where every value "input[i]" will positioned in the "output"
    // NOTE: count will be trasformed in a MAP of where the element "input[i]" will sit
    for (i = 0; i < max_input+1; ++i) {
        c_i = count[i];
        count[i] = total_positioned;
        total_positioned += c_i;
    }

    for (i = 0; i < ilen; ++i) {
        output[count[input[i]]] = input[i];
        ++count[input[i]]; //< 1 place taken for 'input[i]', move right by 1 location
    }

    free(count);

    return output;
}

// The following 2 parameters are fundamental.
// INPUT_SIZE controls how big is the input array
#define INPUT_SIZE  100
// MAX_VALUE_MASK is a mask of bits that caps the maximum value possible
// in the input array. Given how this algorithm works, changing this influences
// directly (temporary) memory usage. Be careful ;)
#define MAX_VALUE_MASK   0xff000000

u_int rand_u_int() {
    // NOTE: RAND_MAX == 0x7fffffff

    u_int res;
    if (rand() >= 0) {
        res = ((rand() | rand()) ^ rand()) & rand();
    } else {
        res = rand() ^ rand() | rand();
    }

    // cap the value: remove all the BITS set to 1 by MAX_VALUE_MASK
    return (res | MAX_VALUE_MASK) ^ MAX_VALUE_MASK;

}

int main() {
    u_int input[INPUT_SIZE],
        *output,
        ilen = INPUT_SIZE,
        i;

    for (i = 0; i < ilen; ++i) {
        input[i] = rand_u_int();
    }
    printf("INPUT ARRAY:\n");
    print_array(input, INPUT_SIZE);
    printf("\n");

    output = counting_sort(input, ilen);
    printf("OUTPUT ARRAY:\n");
    print_array(output, INPUT_SIZE);
    printf("\n");
}
