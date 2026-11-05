// RUN-1: clang -O0 06-ub-overflow.c -o ub0 && ./ub0
// RUN-2: clang -O2 06-ub-overflow.c -o ub2 && ./ub2
// RUN-3: clang -O2 -fwrapv 06-ub-overflow.c -o ubw && ./ubw
// RUN-4: objdump -d ub2 | grep -A2 '<greater>:'

#include <limits.h>
#include <stdio.h>

int greater(int x) {
  return x + 1 > x;
}

int main(void) {
  printf("greater(0) = %d\n", greater(0));
  printf("greater(INT_MAX - 1) = %d\n", greater(INT_MAX - 1));
  printf("greater(INT_MAX) = %d   // signed overflow: UB\n", greater(INT_MAX));
  return 0;
}
