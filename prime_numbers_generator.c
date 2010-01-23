#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned long long ull;
typedef unsigned short int bool;

#define TRUE    1
#define FALSE   0

// Check if a number is a Prime, dividing it by all the other 
//  verified primes < of it's Square value.
bool is_prime(ull *primes, ull primes_found, ull value) {
    ull i;
    // Limit - Never check for primes larger then the sqrt(value)
    ull limit = (ull)sqrt(value);
    
    #ifdef DEBUG
        printf("Value: %llu - Primes found so far: %llu\n", value, primes_found);
    #endif
    
    for ( i = 0; i < primes_found; ++i ) {
        // Check if the value is divisible by this prime
        if ( value % primes[i] == 0 ) return FALSE;
        // Check if it's enough. Limit sqrt(value) exceded
        if ( primes[i] > limit ) break;
    }
    return TRUE;
}

ull* prime_numbers_generator(ull input) {
    ull* primes = NULL;
    ull primes_found = 1;
    ull i, j;
    
    // Allocating memory to store the Primes
    primes = (ull*)malloc(input * sizeof(ull));
    if ( NULL == primes ) return NULL;    
    
    // '2' is the first prime 
    primes[0] = 2;

    primes[1] = 3; // Let's start testing '3' for primality ;)
    for ( i = 1; i < input; ) {
        #ifdef DEBUG
            printf("i: %llu - Potential Prime: %llu\n", i, primes[i]);
        #endif
        // Check if 'primes[i]' is a prime
        if ( is_prime(primes, primes_found, primes[i]) ) {
            #ifdef DEBUG
                printf("Found a new Prime: %llu\n", primes[i]);
            #endif
            // Increment num of primes found so far
            ++primes_found;
            // Move to the next odd number
            primes[++i] = primes[i-1] + 2;
        } else {
            // Move to the next odd number, overriding the current one
            primes[i] += 2;
        }
    }
    
    return primes;
}

int main(int argc, char** argv) {
    ull input, i, *primes = NULL;
    if ( argc == 2 ) input = atoi(argv[1]); else return EXIT_FAILURE;
    
    // Calculate the required primes
    primes = prime_numbers_generator(input);
    if ( NULL == primes ) return EXIT_FAILURE;
    
    #ifndef FAST
    printf("All the first %llu Primes are:\n", input);
    for ( i = 0; i < input; ++i ) {
        printf("%llu ", primes[i]);
    }
    printf("\n\n");
    #endif
    
    printf("The Prime #%llu is %llu\n\n", input, primes[input-1]);
    
    return EXIT_SUCCESS;
}
