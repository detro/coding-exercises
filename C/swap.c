#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}

int main(int argc, char** argv) {
  int a = 10;
  int b = 111;
  int c[] = {1234, 4321};

  printf("a = %d, b = %d\n", a, b);
  printf("c[0] = %d, c[1] = %d\n", c[0], c[1]);

  swap(&a, &b);
  swap(&c[0], &c[1]);

  printf("\n");
  printf("a = %d, b = %d\n", a, b);
  printf("c[0] = %d, c[1] = %d\n", c[0], c[1]);
}
