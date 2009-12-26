#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    unsigned int i, input;
    unsigned long curr = 0, prevprev = 0, prev = 1;
    
    // Check the Input
	if ( argc == 2 ) input = atoi(argv[1]); else return (1);
	if ( input < 0 ) return (1);
	
	if ( input > 0 )
	{
        curr = 1;
        for ( i = 2; i <= input; ++i )
        {
            curr = prevprev + prev;
            #ifdef DEBUG
            printf("%d: %lu\n", i, curr);
            #endif
            prevprev = prev;
            prev = curr;
       }
	}
	
	printf("RESULT: fibonacci(%d) = %lu\n\n", input, curr);
	return (0);
}