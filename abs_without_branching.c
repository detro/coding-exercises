#include <stdio.h>

int abs(const int value) {
   int A = value >> 31;     // 0x00 if Positive, 0xFF if Negative
   int B = -A;              // 0x00 if Positive, 0x01 if Negative
   return (value ^ A) + B;  // value ^ A = value if Positive, value ^ A = ~value if Negative
   // or just: return (value ^ A) - A;
}

int main(int argc, char** argv)
{
    int input;
    
    // Check the Input
	if ( argc == 2 ) input = atoi(argv[1]); else return (1);
	
	printf("abs(%d) = %d\n\n", input, abs(input));
}