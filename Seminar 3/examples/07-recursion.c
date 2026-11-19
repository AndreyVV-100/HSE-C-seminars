// RUN-1: clang -Wall -Wextra 07-recursion.c -o r7 && ./r7
// RUN-2: clang -Wall -Wextra -Werror -DBASELESS 07-recursion.c -o r7b   // error: all paths through this function will call itself
// RUN-3: clang -Wall -Wextra -DBASELESS 07-recursion.c -o r7b2 && ./r7b2   // warning, then segfault
// Recursion = a base case + a step that gets closer to it. Every call has its own n on the stack.

#include <stdio.h>

int fact(int n) {
  if (n == 0)
    return 1;                // base case
  return n * fact(n - 1);    // step
}

int digits(int n) {
  if (n < 10)
    return n;                // base case
  return n % 10 + digits(n / 10);
}

int fact_no_base(int n) {
  return n * fact_no_base(n - 1);   // no base case: -Wall sees this
}

int main(void) {
  printf("fact(3) = %d, fact(0) = %d   // 0! = 1 is the base case\n", fact(3), fact(0));  // 6, 1
  printf("digits(1234) = %d   // 1 + 2 + 3 + 4\n", digits(1234));                        // 10
#ifdef BASELESS
  fflush(stdout);
  printf("fact_no_base(3) = %d\n", fact_no_base(3));   // the chain never stops
#endif
  return 0;
}
