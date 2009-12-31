#include <stdio.h>

unsigned short matrix_2x2_square(unsigned long matrix_array[2][4],
    unsigned short curr_matrix_index)
{
    static int new_matrix_index; new_matrix_index = (curr_matrix_index + 1) % 2;
    matrix_array[new_matrix_index][0] = 
        matrix_array[curr_matrix_index][0] * matrix_array[curr_matrix_index][0]
        + matrix_array[curr_matrix_index][1] * matrix_array[curr_matrix_index][2];
    matrix_array[new_matrix_index][1] = 
        matrix_array[curr_matrix_index][2] * matrix_array[curr_matrix_index][0]
        + matrix_array[curr_matrix_index][3] * matrix_array[curr_matrix_index][2];
    matrix_array[new_matrix_index][2] = 
        matrix_array[curr_matrix_index][0] * matrix_array[curr_matrix_index][1]
        + matrix_array[curr_matrix_index][1] * matrix_array[curr_matrix_index][3];
    matrix_array[new_matrix_index][3] = 
        matrix_array[curr_matrix_index][2] * matrix_array[curr_matrix_index][1]
        + matrix_array[curr_matrix_index][3] * matrix_array[curr_matrix_index][3];

    return new_matrix_index;
}

unsigned short matrix_2x2_multiply_identity(unsigned long matrix_array[2][4],
    unsigned short curr_matrix_index)
{
    static int new_matrix_index; new_matrix_index = (curr_matrix_index + 1) % 2;
    matrix_array[new_matrix_index][0] = matrix_array[curr_matrix_index][0] * 1
        + matrix_array[curr_matrix_index][1] * 1;
    matrix_array[new_matrix_index][1] = matrix_array[curr_matrix_index][2] * 1
        + matrix_array[curr_matrix_index][3] * 1;
    matrix_array[new_matrix_index][2] = matrix_array[curr_matrix_index][0] * 1
        + matrix_array[curr_matrix_index][1] * 0;
    matrix_array[new_matrix_index][3] = matrix_array[curr_matrix_index][2] * 1
        + matrix_array[curr_matrix_index][3] * 0;

    return new_matrix_index;
}

unsigned short matrix_2x2_power(unsigned long matrix_array[2][4],
    unsigned short curr_matrix_index, unsigned short n)
{
    #ifdef DEBUG
    printf("INPUT MATRIX(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
        n, matrix_array[curr_matrix_index][0], matrix_array[curr_matrix_index][1],
        matrix_array[curr_matrix_index][2], matrix_array[curr_matrix_index][3]);
    #endif
    
    if (n > 1)
    {
        if ( n/2 > 1 ) // Avoid useless recursion
        {
            // Recursive call for N/2
            curr_matrix_index = matrix_2x2_power(matrix_array, curr_matrix_index, n/2);
            
            #ifdef DEBUG
            printf("AFTER RECURSION(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
                n, matrix_array[curr_matrix_index][0], matrix_array[curr_matrix_index][1],
                matrix_array[curr_matrix_index][2], matrix_array[curr_matrix_index][3]);
            #endif
        }
        // Matrix = Matrix * Matrix
        curr_matrix_index = matrix_2x2_square(matrix_array, curr_matrix_index);
        
        #ifdef DEBUG
        printf("AFTER MULTIPLICATION(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
            n, matrix_array[curr_matrix_index][0], matrix_array[curr_matrix_index][1],
            matrix_array[curr_matrix_index][2], matrix_array[curr_matrix_index][3]);
        #endif
        
        // If N is odd
        if ( (n % 2) != 0 )
        {
            // Matrix = Matrix * IdentityMatrix ("{1, 1, 1, 0}")
            curr_matrix_index = matrix_2x2_multiply_identity(matrix_array, curr_matrix_index);
            
            #ifdef DEBUG
            printf("AFTER IDENTITY MULTIP.(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
                n, matrix_array[curr_matrix_index][0], matrix_array[curr_matrix_index][1],
                matrix_array[curr_matrix_index][2], matrix_array[curr_matrix_index][3]);
            #endif
        }
    }
        
    #ifdef DEBUG
    printf("RESULT(%d)\n[%lu\t%lu]\n[%lu\t%lu]\n\n",
        n, matrix_array[curr_matrix_index][0], matrix_array[curr_matrix_index][1],
        matrix_array[curr_matrix_index][2], matrix_array[curr_matrix_index][3]);
    #endif

    // Return the index of the matrix carrying the current result
    return curr_matrix_index;
}

unsigned long fibonacci_fast(unsigned short n)
{
    unsigned long   result;
    unsigned short  matrix_2x2_cur = 0;
    unsigned long   matrix_2x2[2][4] = {{1, 1, 1, 0}, {0, 0, 0, 0}};
    
    if ( n > 0)
    {        
        matrix_2x2_cur = matrix_2x2_power(matrix_2x2, matrix_2x2_cur, n-1);
        result = matrix_2x2[matrix_2x2_cur][0];
           
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
