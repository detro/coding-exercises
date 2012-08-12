#include <stdio.h>
#include <sys/types.h>

u_int least_common_multiple(u_int a, u_int b) {
    u_int multi_a = a, factor_a = 1;
    u_int multi_b = b, factor_b = 1;

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
    u_int a, b;

    // Check the Input
    if (argc == 3) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    } else
        return 1;

    printf("Least Common Multiple for '%d' and '%d' is '%d'\n",
        a, b,
        least_common_multiple(a, b));
    return 0;
}
