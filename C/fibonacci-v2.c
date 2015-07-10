#include <stdio.h>
#include <stdlib.h>

unsigned long* matrix_2x2_multiply(unsigned long* A, unsigned long* B)
{
    unsigned long* result = (unsigned long*)malloc(4 * sizeof(unsigned long));
    result[0] = A[0] * B[0] + A[1] * B[2];
    result[1] = A[2] * B[0] + A[3] * B[2];
    result[2] = A[0] * B[1] + A[1] * B[3];
    result[3] = A[2] * B[1] + A[3] * B[3];
    return result;
}

unsigned long* matrix_2x2_multiply_identity(unsigned long* A)
{
    unsigned long identity[] = {1, 1, 1, 0};
    return matrix_2x2_multiply(A, identity);
}

unsigned long* matrix_2x2_power(unsigned long* input_matrix, unsigned short n)
{
    #ifdef DEBUG
    printf("INPUT MATRIX(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
        n, input_matrix[0], input_matrix[1], input_matrix[2], input_matrix[3]);
    #endif

    unsigned long* result = input_matrix;
    unsigned long* temp = NULL;
    
    if (n > 1)
    {
        if ( n/2 > 1 ) // Avoid useless recursion
        {
            result = matrix_2x2_power(input_matrix, n/2);
            temp = result;
            
            #ifdef DEBUG
            printf("AFTER RECURSION(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
                n, result[0], result[1], result[2], result[3]);
            #endif
        }
        result = matrix_2x2_multiply(result, result);
        // Free a 2x2 Array that is not needed anymore
        if ( temp != NULL )
        {
            free(temp);
            temp = NULL;
        }
        
        #ifdef DEBUG
        printf("AFTER MULTIPLICATION(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
            n, result[0], result[1], result[2], result[3]);
        #endif
        
        if ( (n % 2) != 0 )
        {
            result = matrix_2x2_multiply_identity(result);
            
            #ifdef DEBUG
            printf("AFTER IDENTITY MULTIP.(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
                n, result[0], result[1], result[2], result[3]);
            #endif
        }
    }
        
    #ifdef DEBUG
    printf("resultULT(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
        n, result[0], result[1], result[2], result[3]);
    #endif

    return result;
}

unsigned long fibonacci_fast(unsigned short n)
{
    unsigned long result;
    unsigned long* matrix_2x2;
    unsigned long* identity_matrix_2x2;
    
    if ( n > 0)
    {
        // Allocating an initial Array 2x2 of unsigned long
        identity_matrix_2x2 = (unsigned long*)malloc(4 * sizeof(unsigned long));
        // Initialize the first matrix to the "identity matrix"
        identity_matrix_2x2[0] = 1;
        identity_matrix_2x2[1] = 1;
        identity_matrix_2x2[2] = 1;
        identity_matrix_2x2[3] = 0;
        
        matrix_2x2 = matrix_2x2_power(identity_matrix_2x2, n-1);
        result = matrix_2x2[0];
        
        // Freeing memory
        free(identity_matrix_2x2);
        // For "n" < 3 there is the risk that the call "matrix_2x2_power"
        //  returns the same matrix as result: this happens when no
        //  alteration is done on the input matrix.
        if ( identity_matrix_2x2 != matrix_2x2 )
            free(matrix_2x2);
            
        return result;
    }
    else
        return 0;
}

int main(int argc, char** argv)
{
    unsigned short input;
    // Check the Input
	if ( argc == 2 ) input = atoi(argv[1]); else return (1);

	printf("RESULT: fibonacci-v2(%d) = %lu\n\n", input, fibonacci_fast(input));
	return (0);
}
