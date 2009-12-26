#include <stdio.h>
#include <stdlib.h>

unsigned long* matrix_2x2_multiply(unsigned long* A, unsigned long* B)
{
    unsigned long* res = (unsigned long*)malloc(4 * sizeof(unsigned long));
    res[0] = A[0] * B[0] + A[1] * B[2];
    res[1] = A[2] * B[0] + A[3] * B[2];
    res[2] = A[0] * B[1] + A[1] * B[3];
    res[3] = A[2] * B[1] + A[3] * B[3];
    return res;
}

unsigned long* matrix_2x2_multiply_identity(unsigned long* A)
{
    unsigned long identity[] = {1, 1, 1, 0};
    return matrix_2x2_multiply(A, identity);
}

unsigned long* matrix_2x2_power(unsigned long* input_matrix, int n)
{
    #ifdef DEBUG
    printf("INPUT MATRIX(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
        n, input_matrix[0], input_matrix[1], input_matrix[2], input_matrix[3]);
    #endif

    unsigned long* res = input_matrix;
    unsigned long* temp = NULL;
    
    if (n > 1)
    {
        if ( n/2 > 1 ) // Avoid useless recursion
        {
            res = matrix_2x2_power(input_matrix, n/2); // 
            temp = res;
            
            #ifdef DEBUG
            printf("AFTER RECURSION(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
                n, res[0], res[1], res[2], res[3]);
            #endif
        }
        res = matrix_2x2_multiply(res, res);
        if ( temp != NULL )
        {
            free(temp);
            temp = NULL;
        }
        
        #ifdef DEBUG
        printf("AFTER MULTIPLICATION(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
            n, res[0], res[1], res[2], res[3]);
        #endif
        
        if ( (n % 2) != 0 )
        {
            res = matrix_2x2_multiply_identity(res);
            
            #ifdef DEBUG
            printf("AFTER IDENTITY MULTIP.(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
                n, res[0], res[1], res[2], res[3]);
            #endif
        }
    }
        
    #ifdef DEBUG
    printf("RESULT(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
        n, res[0], res[1], res[2], res[3]);
    #endif

    return res;
}

unsigned long fibonacci_fast(unsigned long n)
{
    unsigned long res;
    unsigned long* matrix_2x2;
    unsigned long* identity_matrix_2x2;
    
    if ( n > 0)
    {
        identity_matrix_2x2 = (unsigned long*)malloc(4 * sizeof(unsigned long));
        identity_matrix_2x2[0] = identity_matrix_2x2[1] = 1;
        identity_matrix_2x2[2] = 1; identity_matrix_2x2[3] = 0;
        
        matrix_2x2 = matrix_2x2_power(identity_matrix_2x2, n-1);
        res = matrix_2x2[0];
        free(identity_matrix_2x2);
        if ( identity_matrix_2x2 != matrix_2x2 )
            free(matrix_2x2);
            
        return res;
    }
    else
        return 0;
}

int main(int argc, char** argv)
{
    int input;
    // Check the Input
	if ( argc == 2 ) input = atoi(argv[1]); else return (1);
	if ( input < 0 ) return (1);

	printf("RESULT: fibonacci-v2(%d) = %lu\n\n", input, fibonacci_fast(input));
	return (0);
}