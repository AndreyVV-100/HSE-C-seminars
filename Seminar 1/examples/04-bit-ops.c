// RUN: clang -Wall -Wextra 04-bit-ops.c -o 04-bit-ops
// The x & 1 == 0 line triggers -Wparentheses: == binds tighter than &.

#include <stdio.h>

void print_binary(unsigned int value);

int main(void) {
  unsigned int x = 10U;   // 1010
  unsigned int y = 12U;   // 1100

  printf("x = %u: ", x); print_binary(x); putchar('\n');
  printf("y = %u: ", y); print_binary(y); putchar('\n');

  printf("x & y = %u (1000)\n", x & y);
  printf("x | y = %u (1110)\n", x | y);
  printf("x ^ y = %u (0110)\n", x ^ y);
  printf("x << 1 = %u (10100)\n", x << 1);
  printf("y >> 2 = %u (0011)\n", y >> 2);
  printf("~0u = %u (UINT_MAX)\n", ~0u);

  int priority1 = x & 1 == 0;
  int priority2 = (x & 1) == 0;
  printf("x & 1 == 0 → %d\n", priority1);
  printf("(x & 1) == 0 → %d\n", priority2);

  int v = -8;
  printf("-8 >> 1 = %d (implementation-defined: arithmetic shift)\n", v >> 1);
  printf("(unsigned)(-8) >> 1 = %u\n", (unsigned)(-8) >> 1);
  return 0;
}

void print_binary(unsigned int value) {
  for (unsigned int pos = 8U; pos > 0U; --pos) {
    putchar(((value >> (pos - 1U)) & 1U) ? '1' : '0');
  }
}
