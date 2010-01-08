#include <stdio.h>
#include <string.h>
#include <math.h>

#define NORM_CHAR(A)    (A - ' ')
#define ALPHABET_SIZE   (NORM_CHAR(255)+1)
#define LLU_POW(x, y)   (unsigned long long)pow(x, y)

unsigned long long hash_char(const char* string, unsigned int pos, unsigned int size) {
    #ifdef DEBUG
    printf("HASHING of char '%c' (of value %d) in position #%d of a string of size %d is: %llu\n",
        string[pos],
        NORM_CHAR(string[pos]),
        pos,
        size,
        LLU_POW(ALPHABET_SIZE, size - (pos + 1)) * NORM_CHAR(string[pos])
        );
    #endif
        
    return LLU_POW(ALPHABET_SIZE, size - (pos + 1)) * NORM_CHAR(string[pos]);
}

/**
Given that:
- 'S' is the String in which we are searching (i.e. 'A')
- 'j' is position of the last char in 'S' included in the Hashing
- 'alpha' is the size of the Alphabet
- 'm' is the size of the string being searched (i.e. 'B_size')

=> Hashing(S, j) = SUMMATION [i=0 -> m-1] { alpha^(m -(i+1)) * char(S[i+j]) }
*/
unsigned long long hash_string(const char* string, unsigned int size) {
    static unsigned int i;
    static unsigned long long hash;

    hash = 0;
    for ( i = 0; i < size; ++i ) {
        hash += hash_char(string, i, size);
    }
    
    return hash;
}

int main(int argc, char** argv)
{
    char* A;
    char* B;
    unsigned long long A_hash;
    unsigned long long B_hash;
    unsigned int B_size;
    unsigned int i;
    
    // Check the Input
	if ( argc == 3 ) {
	   A = argv[1];
	   B = argv[2];
	}
	else
	   return (1);

    // Calculate initial Hashings
    B_size = strlen(B);
    A_hash = hash_string(A, B_size);
    B_hash = hash_string(B, B_size);
    printf("HASHING of B('%s') is: %llu\n", B, B_hash);
    #ifdef DEBUG
    printf("Starting from char in position %d, the HASHING of A for length %d is: %llu\n",
        0, B_size, A_hash);
    #endif

    i = B_size;
    while ( A[i-1] != '\0' ) {
        if ( A_hash == B_hash ) {
            printf("YES! B is a Substring of A, in the range {%d, %d}\n\n",
                i-B_size, i-1);
            return(0);
        } else {
            // 'S' is the String in which we are searching (i.e. 'A')
            // 'j' is position of the last char in 'S' included in the Hashing
            // 'alpha' is the size of the Alphabet
            // 'm' is the size of the string being searched (i.e. 'B_size')
            //
            // H(S, j+1) = alpha * ( H(S, j) - alpha^(m-1) * char(S[j]) ) + char(S[j+m])
            A_hash = ALPHABET_SIZE
                * (
                    A_hash
                    - LLU_POW(ALPHABET_SIZE, (B_size-1))
                    * NORM_CHAR( A[i-B_size] )
                )
                + NORM_CHAR( A[i++] );
            #ifdef DEBUG
            printf("Starting from char in position %d, the HASHING of A for length %d is: %llu\n",
                i-B_size, B_size, A_hash);
            #endif
        }
    }
    printf("NO. B is not a Substring of A\n\n", B_hash, A_hash);
}