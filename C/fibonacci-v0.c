#include <stdio.h>

unsigned long fibonacci_slow(unsigned short i)
{
    if ( i == 0 )
        return (0);
    
    if ( i == 1 )
        return (1);
    
    return ( fibonacci_slow(i-1) + fibonacci_slow(i-2) );
}

int main(int argc, char** argv)
{
    unsigned short i, input;
    unsigned long curr = 0, prevprev = 0, prev = 1;
    
    // Check the Input
	if ( argc == 2 ) input = atoi(argv[1]); else return (1);
	
	printf("RESULT: fibonacci(%d) = %lu\n\n", input, fibonacci_slow(input));
	return (0);
}