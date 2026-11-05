// RUN: clang -Wall -Wextra 03-int-arith.c -o 03-int-arith
// Shifts and INT_MAX + 1 are UB: clang warns and prints garbage values.

#include <limits.h>
#include <stdio.h>

int main(void) {
  printf("5 / 2 = %d, 5 %% 2 = %d\n", 5 / 2, 5 % 2);
  printf("-5 / 2 = %d, -5 %% 2 = %d   (truncation toward zero)\n", -5 / 2, -5 % 2);

  double a = 5 / 2;
  double b = (double)5 / 2;
  printf("double a = 5 / 2      → %.1f\n", a);
  printf("double b = (double)5 / 2 → %.1f\n", b);
  printf("int c = 3.9           → %d\n", (int)3.9);

  printf("1 << 40   (int, UB)  = %d\n", 1 << 40);
  printf("1LL << 40 (OK)       = %lld\n", 1LL << 40);
  printf("INT_MAX + 1 (int, UB) = %d\n", INT_MAX + 1);
  printf("UINT_MAX + 1u (defined, modular) = %u\n", UINT_MAX + 1u);

  printf("2000000000 * 2 (int, UB) = %d\n", 2000000000 * 2);
  printf("2000000000LL * 2 (OK)    = %lld\n", 2000000000LL * 2);
  return 0;
}
