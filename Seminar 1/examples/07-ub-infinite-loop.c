// RUN-1: clang -O0 07-ub-infinite-loop.c -o loop0 && timeout 2 ./loop0   // hangs, no output
// RUN-2: clang -O2 07-ub-infinite-loop.c -o loop2 && ./loop2   // loop removed, garbage exit code
// Infinite loop without side effects is UB, so the compiler may delete it.

#include <stdio.h>

void unreachable_function(void) {
  printf("You would never see this!\n");
}

int main(void) {
  unsigned int x = 0;

  while (x >= 0) {
    x = x + 1;
  }

  printf("loop ended, x = %u\n", x);
  unreachable_function();
  return 0;
}
