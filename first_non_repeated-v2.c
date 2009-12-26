/**
Determine the first non-repeated character in a word. For example, in abbcaf it should return c.
Do this in O(n) time with O(1) space.
*/

// NOTE 1: It assumes lowcase input: some conversion/adaptation could be introduced for completeness.
// NOTE 2: It avoids to use of strlen to calculates the length of the input. This makes the solution a "2 * O(n) == O(n)" => VERY COOL
// NOTE 3: The space occupied is "O(1)" (constant) => 1 pointer, 2 support unsigned int, 1 unsigned char [25]
// NOTE 4: The logic of this solution is based on the usage of an array of unsigned chars.
//         Every char (assumed to be lowecase) has an associated small byte (1 char = 8 bits), where the bits 0x1 and 0x2 (the 2 least significant)
//         represent, respectively, "present once in the input string" and "present multiple times in the input string".
//         After the input is "scanned" once, and every letter is marked with the correspondent "presence bit" (once, multiple or none), it get's
//         scanned a second time to find the first char of the input which has the bit "present once" set to "1".

#include <stdio.h>
#include <string.h>

#define PRESENCE_ONCE_BIT       0x1
#define PRESENCE_MULTIPLE_BIT   0x2
#define NORMALIZE_CHAR(C)       (C-'a')

int main(int argc, char** argv)
{
	char* input;
	unsigned int input_length;
	unsigned int i;

	unsigned char char_presence_bitmask[26];
	memset(char_presence_bitmask, 0x0, 26);

	// Check the Input
	if ( argc == 2 ) input = argv[1];
	else return (1);

    // Search for every character "present only once"
    for ( i = 0;; ++i )
    {
        // Avoid use of "strlen", just to look cooler
        if ( input[i] != '\0' )
        {
            // If the current char is not already marked as "present multiple times"
            if ( !( char_presence_bitmask[NORMALIZE_CHAR(input[i])] & PRESENCE_MULTIPLE_BIT) )
            {
                // It it is already marked as "present once"
                if ( char_presence_bitmask[NORMALIZE_CHAR(input[i])] & PRESENCE_ONCE_BIT )
                {
                    // Then mark it as "present multiple times" and unmark it's "present once" bits
                    char_presence_bitmask[NORMALIZE_CHAR(input[i])] |= PRESENCE_MULTIPLE_BIT;
                    char_presence_bitmask[NORMALIZE_CHAR(input[i])] &= ~PRESENCE_ONCE_BIT;
                }
                else
                {
                    // Otherwise, mark it as "present once"
                    char_presence_bitmask[NORMALIZE_CHAR(input[i])] |= PRESENCE_ONCE_BIT;
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
        if ( char_presence_bitmask[NORMALIZE_CHAR(input[i])] & PRESENCE_ONCE_BIT )
        {
            printf("=== FINAL RESULT: %c ===\n", input[i]);
            return (0);
        }
    }
    printf("=== FINAL RESULT: no char appears only once ===\n");
    return (0);
}
