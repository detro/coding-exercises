#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void permute(char * str, unsigned int start, unsigned int end) {
    static int counter = 1;
    char tmp;
    unsigned int i;

    if (start == end) {
        printf("%d: %s\n", counter, str);
        ++counter;
    } else {
        for (i = start; i < end; ++i) {
            // swap i and start
            tmp = str[i];
            str[i] = str[start];
            str[start] = tmp;

            permute(str, start+1, end);

            // swap i and start
            tmp = str[i];
            str[i] = str[start];
            str[start] = tmp;
        }
    }
}

int main(int argc, char** argv)
{
    char *input = NULL;

    // Check the Input
    if ( argc == 2 )
        input = argv[1];
    else
        return (1);

    permute(input, 0, strlen(input));
    return (0);
}
