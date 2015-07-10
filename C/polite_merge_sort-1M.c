#include <stdio.h>
#include <stdlib.h>

// === Polite Merge Sort ===
// This implementation of Merge Sort is defined "polite", because it tries
// to bother the Operating Systems as less as possible.
//
// Instead of allocating and freeing memory at every intermediate step
// to implement a the priority queue required to sort do the "MERGE STEP",
// it requires to pass at input an empty support array of the same size
// of the input array.
//
// The support array is going to be the solely memory used as support.

void polite_merge(int* array, const unsigned int l_limit, const unsigned int m_limit, const unsigned int r_limit, int* support_array) {
    // Create 3 Peace Marker
    unsigned int i; // For the 'array'
    unsigned int j; // For the 'left part of the array already ordered'
    unsigned int k; // For the 'right part of the array already ordered'
    
    // Copy the portion of sorted arrays in the support array (like a static priority queue)
    for ( i = l_limit; i <= r_limit; ++i ) {
        support_array[i] = array[i];
    }
    
    // Set the Peace Markers
    i = j = l_limit; // 'i' and 'j' both start from the Left
    k = m_limit + 1; // 'k' starts from the Middle + 1 
    
    // Merge the 2 sorted portions
    while ( j <= m_limit && k <= r_limit ) {
        if ( support_array[j] < support_array[k] )
            array[i++] = support_array[j++];
        else
            array[i++] = support_array[k++];
    }
    // Add the remaining sorted portions (if any)
    while ( j <= m_limit ) array[i++] = support_array[j++];
    while ( k <= r_limit ) array[i++] = support_array[k++];
}

void polite_merge_sort(int* array, const unsigned int l_limit, const unsigned int r_limit, int* support_array) {
    unsigned int middle;
    
    if ( l_limit == r_limit ) {
        // Nothing to do => Only 1 element - already sorted
    } else if ( 1 == r_limit - l_limit ) {
        // Only 2 elements - swap them if not yet sorted
        if ( array[r_limit] < array[l_limit] ) {
            // Swap in place - cool!
            array[r_limit] ^= array[l_limit];
            array[l_limit] ^= array[r_limit];
            array[r_limit] ^= array[l_limit];
        }
    } else {
        middle = (l_limit + r_limit) / 2;
        polite_merge_sort(array, l_limit, middle, support_array);
        polite_merge_sort(array, middle + 1, r_limit, support_array);
        polite_merge(array, l_limit, middle, r_limit, support_array);
    }
}

int main(const int argc, const char** argv) {
    #define INPUT_ARRAY_SIZE 1000000 // YES! 1 Million

    int i;
    int *arr;
    arr = malloc(INPUT_ARRAY_SIZE * sizeof(int));
    int sup_arr[INPUT_ARRAY_SIZE];
    
    sranddev();
    for ( i = 0; i < INPUT_ARRAY_SIZE; ++i ) {
        arr[i] = rand();
    }
    
    polite_merge_sort(arr, 0, INPUT_ARRAY_SIZE-1, sup_arr);
    
    printf("----- SOLUTION -----\n");
    for ( i = 0; i < INPUT_ARRAY_SIZE; ++i ) {
        printf("#%d: %d\n", i, arr[i]);
    }
    printf("\n------- END --------\n");
}