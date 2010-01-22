/*
There is an array A[N] of N numbers.
You have to compose an array Output[N] such that Output[i] will be equal
to multiplication of all the elements of A[N] except A[i].

For example Output[0] will be multiplication of A[1] to A[N-1] and Output[1]
will be multiplication of A[0] and from A[2] to A[N-1].

Solve it without division operator and in O(n).
*/

#include <stdio.h>
#include <stdlib.h>

int *bidirectionally_multiplied_array(const int *A, int size_A) {
    int *multi_left_to_right, *multi_right_to_left, *output;
    int i;
    
    // Make some space for calculation...
    multi_left_to_right = malloc(size_A * sizeof(int));
    multi_right_to_left = malloc(size_A * sizeof(int));
    output = malloc(size_A * sizeof(int));
    
    // Multiply the elements "from left to right"...
    multi_left_to_right[0] = A[0];
    for ( i = 1; i < size_A; ++i ) {
        multi_left_to_right[i] = multi_left_to_right[i-1] * A[i];
    }
    
    // Multiply the elements "from right to left"...
    multi_right_to_left[size_A-1] = A[size_A-1];
    for ( i = size_A-2; i >= 0; --i ) {
        multi_right_to_left[i] = multi_right_to_left[i+1] * A[i];
    }
    
    // First and Last element are "special case"
    output[0] = multi_right_to_left[1];
    output[size_A-1] = multi_left_to_right[size_A-2];
    for ( i = 1; i < size_A-1; ++i ) {
        output[i] = multi_left_to_right[i-1] * multi_right_to_left[i+1];
    }
    
    free(multi_left_to_right);
    free(multi_right_to_left);
    
    return output;
}

int main(int argc, char** argv) {
    #define INPUT_ARRAY_SIZE 11
    int input_array[INPUT_ARRAY_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int *output_array;
    int i;
    
    printf("INPUT ARRAY:\n");
    printf("[ ");
    for ( i = 0; i < INPUT_ARRAY_SIZE; ++i ) { printf("%d ", input_array[i]); }
    printf("]\n");
    
    output_array = bidirectionally_multiplied_array(input_array, INPUT_ARRAY_SIZE);
    
    printf("OUTPUT ARRAY:\n");
    printf("[ ");
    for ( i = 0; i < INPUT_ARRAY_SIZE; ++i ) { printf("%d ", output_array[i]); }
    printf("]\n");
    
    free(output_array);
}