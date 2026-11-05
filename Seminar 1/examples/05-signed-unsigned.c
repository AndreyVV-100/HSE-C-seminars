// RUN: clang -Wall -Wextra 05-signed-unsigned.c -o 05-signed-unsigned
// -Wsign-compare warns about the comparisons below: that is the point.

#include <limits.h>
#include <stdio.h>

int main(void) {
  if (-1 < 1u) {
    puts("yes");
  } else {
    puts("no");
  }
  printf("(unsigned)-1 = %u = UINT_MAX = %u\n", (unsigned)-1, UINT_MAX);

  return 0;
}
