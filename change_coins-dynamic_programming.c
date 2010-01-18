#include <stdio.h>
#include <stdlib.h>

unsigned int* change_coins_dynpro(unsigned short int D[],
    unsigned int D_size, unsigned int amount) {
    // Min. num. of coins for the given 'amount'
    unsigned int min_num_coins[amount], cur_min_num_coins;
    // Biggest coin used for the given 'amount'
    unsigned int biggest_coin_at[amount], cur_biggest_coin_at;
    
    unsigned int i, j;
    unsigned int* solution = NULL;
    
    // Ensure the Denomination System can represent any value
    if ( D[0] != 1 ) return NULL;
    
    // Initialize the solution array to Zero
    solution = (unsigned int*)calloc(D_size, sizeof(unsigned int));
    if ( NULL == solution ) {
        return NULL;
    }

    // Amount '0' requires '0' coins
    min_num_coins[0] = 0;
    biggest_coin_at[0] = 0;
    
    // For Amounts from '1' to 'amount'
    for ( i = 1; i <= amount; ++i ) {
        // Start taking 'D[0]' 'i-times'
        cur_min_num_coins = (i / D[0]);
        cur_biggest_coin_at = 0;

        // For coins from 'D[1]' to 'D[D_size -1]'
        for ( j = 1; j < D_size; ++j ) {
            // If 'D[j]' minimizes the num. of coins to take for amount 'i'
            if ( (i >= D[j]) && (cur_min_num_coins >= (min_num_coins[ i - D[j] ] +1)) ) {
                cur_min_num_coins = min_num_coins[ i - D[j] ] +1;
                cur_biggest_coin_at = j;
            }
        }
        
        // Store the minimum just found
        min_num_coins[i] = cur_min_num_coins;
        biggest_coin_at[i] = cur_biggest_coin_at;
    }
    
    // Let's build the solution array
    while ( amount > 0 ) {
        cur_biggest_coin_at = biggest_coin_at[amount];
        
        solution[ cur_biggest_coin_at ] += 1; // Add '1' of this coin to the solution
        amount -= D[cur_biggest_coin_at]; // Amount left when picking this coin
    }
    
    return solution;
}

int main(int argc, char** argv) {
    // Weird coins
    #define NUM_DENOMINATIONS 4
    unsigned short int denominations[NUM_DENOMINATIONS] = {1, 10, 30, 40};
    
    /*
    // Euro, multiplied by 100 (to normalize so 1c is 1)
    #define NUM_DENOMINATIONS 14
    unsigned short int denominations[NUM_DENOMINATIONS] = {1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 50000};
    */
    
    unsigned int* sol;
    unsigned int input, i;
    
    if ( argc == 2 ) input = atoi(argv[1]); else return EXIT_FAILURE;
    
    printf("Given the Money System of Denominations:\n[ ");
    for ( i = 0; i < NUM_DENOMINATIONS; ++i ) { printf("%d ", denominations[i]); }
    printf("]\n");
    
    sol = change_coins_dynpro(denominations, NUM_DENOMINATIONS, input);
    if ( NULL != sol ) {
        printf("The minimum of coins to represent the Amount %d is:\n", input);
        for ( i = 0; i < NUM_DENOMINATIONS; ++i ) {
            printf("#%d coin(s) of value %d\n", sol[i], denominations[i]);
        }
        free (sol); // Cleanup
    } else
        printf("ERROR");
    
    return (EXIT_SUCCESS);
}