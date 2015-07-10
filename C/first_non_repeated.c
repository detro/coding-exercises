/**
Determine the first non-repeated character in a word. For example, in abbcaf it should return c.
Do this in O(n) time with O(1) space.
*/

// NOTE 1: It assumes lowcase input: some conversion/adaptation could be introduced for completeness.
// NOTE 2: Works as long as the set of chars is < number_of_bits(int) (normally is 32)
// NOTE 3: The output is reconstructed from an Hexadecimal value where the result is the first bit (from right to left) set to "1"
// NOTE 4: It avoids to use of strlen to calculates the length of the input. This makes the solution a "2 * O(n) == O(n)" => VERY COOL
// NOTE 5: The space occupied is "O(1)" (constant) => 1 pointer, 2 support unsigned int, 2 solution-carrying unsigned int, 1 hashmap of SIZE_OF_ALPHABET int

#define NORMALIZE_CHAR(C)       (C-'a')

#include <stdio.h>

int main(int argc, char** argv)
{
	char* input;
	unsigned int input_length;
	unsigned int i;

	unsigned int present_once = 0;
	unsigned int present_multiple = 0;

	const unsigned int char_to_bit[26] = {
	   0x1, 0x2, 0x4, 0x8, // a, b, c, d
	   0x10, 0x20, 0x40, 0x80, // ...
	   0x100, 0x200, 0x400, 0x800,
	   0x1000, 0x2000, 0x4000, 0x8000,
	   0x10000, 0x20000, 0x40000, 0x80000, //...
	   0x100000, 0x200000, 0x400000, 0x800000, // u, v, w, x
	   0x1000000, 0x2000000 // y, z
	   };

	// Check the Input
	if ( argc == 2 ) input = argv[1];
	else return (1);

    // Search for every character "present only once"
    for ( i = 0; ; ++i )
    {
        if ( input[i] != '\0' ) ///< Doesn't use "strlen" - It checks at every iteration if we reached the end of the string
        {
            // If the current char is not already marked as "present multiple times"
            if ( !( present_multiple & char_to_bit[ NORMALIZE_CHAR(input[i]) ] ) )
            {
                // It it is already marked as "present once"
                if ( present_once & char_to_bit[ NORMALIZE_CHAR(input[i]) ] )
                {
                    // Then mark it as "present multiple times" and unmark it's "present once"
                    present_multiple |= char_to_bit[ NORMALIZE_CHAR(input[i]) ];
                    present_once &= ~char_to_bit[ NORMALIZE_CHAR(input[i]) ];
                }
                else
                {
                    // Otherwise, mark it as "present once"
                    present_once |= char_to_bit[ NORMALIZE_CHAR(input[i]) ];
                }
            }
        }
        else
        {
            // Store the input length to make next iteration easier
            input_length = i;
            break;
        }
    }

    // Look for the first char that is marked as "present only once" => that's the solution
    for ( i = 0; i < input_length; ++i )
    {
        if ( present_once & char_to_bit[ NORMALIZE_CHAR(input[i]) ] )
        {
            printf("=== FINAL RESULT: %c ===\n", input[i]);
            return (0);
        }
    }
    printf("=== FINAL RESULT: no char appears only once ===\n", input[i]);
    return (0);
}
