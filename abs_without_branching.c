#include <stdio.h>

int absolute(const int value) {
   int A = value >> 31;     // 0x00 == 0 if value was Positive, 0xFF == -1 if value was Negative
   int B = -A;              // 0x00 == 0 if value was Positive, 0x01 == 1 if value was Negative

   return (value ^ A) + B;  // (value ^ A) = value if value was Positive,
                            // or (value ^ A) = complement(value) if value was Negative
   // or just: return (value ^ A) - A;
}

int main(int argc, char** argv)
{
    int input;

    // Check the Input
	if ( argc == 2 ) input = atoi(argv[1]); else return (1);

	printf("abs(%d) = %d\n\n", input, absolute(input));
}
