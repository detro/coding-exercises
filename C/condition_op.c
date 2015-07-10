#include <stdio.h>
#include <stdlib.h>

int condition(int x, int a, int b) {
    int norm_x = !!x;
    return (a + b) - (b * norm_x) - ( a * !norm_x);
}

int main(int argc, char** argv) {
    int x, a, b;
    if ( argc == 4 ) {
        x = atoi(argv[1]);
        a = atoi(argv[2]);
        b = atoi(argv[3]);
    } else
        return EXIT_FAILURE;
    
    printf("%d ? %d : %d = %d\n", x, a, b, condition(x, a, b));
    return EXIT_SUCCESS;
}