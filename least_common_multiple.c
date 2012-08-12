#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>

u_long least_common_multiple(u_long a, u_long b) {
    u_long multi_a = a, factor_a = 1;
    u_long multi_b = b, factor_b = 1;

    while(multi_a != multi_b) {
        if (multi_a < multi_b) {
            multi_a = a * ++factor_a;
        } else if (multi_b < multi_a) {
            multi_b = b * ++factor_b;
        }
    }

    return multi_a; //< or multi_b, as they are the same :)
}

int main(int argc, char** argv)
{
    u_long a, b;

    // Check the Input
    if (argc == 3) {
        a = strtol(argv[1], NULL, 10);
        b = strtol(argv[2], NULL, 10);
    } else
        return 1;

    printf("Least Common Multiple for '%lu' and '%lu' is '%lu'\n",
        a, b,
        least_common_multiple(a, b));
    return 0;
}
