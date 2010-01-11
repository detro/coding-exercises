#include <stdio.h>
#include <stdlib.h>

void print_row(unsigned long long* row, unsigned int size) {
    static unsigned int j;
    for ( j = 0; j < size; ++j ) { printf("%llu ", row[j]); }
    printf("\n");
}

unsigned long long* pascal_triangle_line(unsigned int pascal_row){
    static unsigned int i, j;
    unsigned long long* result = NULL;
    result = (unsigned long long*)calloc(pascal_row, sizeof(unsigned long long));
    
    if ( NULL != result ) {    
        result[pascal_row-1] = 1; // First element on the right is always '1'
        for ( i = 2; i <= pascal_row; ++i ) {
            
            #ifdef DEBUG
            print_row(result, pascal_row);
            #endif
            
            for ( j = pascal_row-i; j < pascal_row-1; ++j ) {
                result[j] += result[j+1]; // Calculate the 'j'-th element
                
                #ifdef VERBOSE
                printf("(row: %d, element: %d) => %llu\n", i, j, result[j]);
                #endif
            }
        }
    }
        
    return (result);
}

int main(int argc, char** argv)
{
    unsigned int input;
    unsigned long long* result = NULL;
       
    // Check the Input
	if ( argc == 2 ) input = atoi(argv[1]); else return (EXIT_FAILURE);
    
    // Calculate the required line
    result = pascal_triangle_line(input);
    
    // Print result
    if ( NULL != result ) { 
        printf("RESULT ROW:\n");
        print_row(result, input);
        return (EXIT_SUCCESS);
    }
    return (EXIT_FAILURE);
}
