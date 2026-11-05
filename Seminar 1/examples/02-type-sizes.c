// RUN: clang -Wall -Wextra -Werror 02-type-sizes.c -o 02-type-sizes

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
  printf("char        %2zu bytes (CHAR_BIT = %d bits)\n", sizeof(char), CHAR_BIT);
  printf("short       %2zu\n", sizeof(short));
  printf("int         %2zu\n", sizeof(int));
  printf("long        %2zu\n", sizeof(long));
  printf("long long   %2zu\n", sizeof(long long));
  printf("float       %2zu\n", sizeof(float));
  printf("double      %2zu\n", sizeof(double));
  printf("long double %2zu\n", sizeof(long double));
  printf("bool        %2zu\n", sizeof(bool));
  printf("int32_t     %2zu, int64_t %2zu\n", sizeof(int32_t), sizeof(int64_t));

  printf("INT_MAX = %d, INT_MIN = %d, UINT_MAX = %u\n", INT_MAX, INT_MIN, UINT_MAX);

  char a = 100, b = 100;
  printf("a + b = %d, sizeof(a + b) = %zu\n", a + b, sizeof(a + b));
  printf("int + double: sizeof(1 + 2.0) = %zu\n", sizeof(1 + 2.0));
  printf("int + unsigned, same rank: sizeof(-5 + 2u) = %zu, value = %u\n",
         sizeof(-5 + 2u), -5 + 2u);

  printf("sizeof('A') = %zu: character literal has type int\n", sizeof('A'));
  return 0;
}
