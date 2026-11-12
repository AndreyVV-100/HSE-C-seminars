// RUN-1: clang -Wall -Wextra 04-printf-specs.c -o pf4 && ./pf4
// RUN-2: gcc -Wall -Wextra 04-printf-specs.c -o pf4g && ./pf4g
// The last printf is UB: %d expects int, the argument is double. -Wall catches it.

#include <stdio.h>

int main(void) {
  int n = 42;
  double pi = 3.14159;
  long big = 100000L;
  long long huge = 100000000000LL;
  unsigned uint_val = 42U;

  printf("n = %d, pi = %f\n", n, pi);                 // n = 42, pi = 3.141590
  printf("%u %x %o %c %s %%\n", uint_val, uint_val, uint_val, 'A', "text");
  printf("flags/width/precision: [%08.3f] [%10.2f] [%-8d]\n", pi, pi, n);
  printf("scientific: %e, compact: %g\n", 1234.5, 1234.5);
  printf("length modifiers: %ld, %lld\n", big, huge);
  printf("sizeof is size_t: %zu\n", sizeof(int));     // not %d
  printf("long double: %Lf\n", 3.14L);
  printf("address of n: %p\n", (void *)&n);           // %p wants void *

  int printed = printf("float promotes to double: %f\n", 1.5f);   // %f is fine for float
  printf("printf returned %d\n", printed);            // number of characters printed

  printf("%d\n", 3.5);                                // UB: garbage, changes from run to run
  return 0;
}
