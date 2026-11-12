// RUN-1: clang -Wall -Wextra 05-scanf.c -o sc5 && printf '12 7 2.5\n' | ./sc5   // d = 2.500000
// RUN-2: printf 'abc\n' | ./sc5      // no numbers: scanf returns 0, program exits with 1
// RUN-3: clang -Wall -Wextra -DBAD_SCANF 05-scanf.c -o sc5b && printf '12 7 2.5\n' | ./sc5b   // d = 0.000000

#include <stdio.h>

int main(void) {
  int a = 0, b = 0;
  int got = scanf("%d%d", &a, &b);        // scanf needs addresses: &a, &b
  printf("scanf read %d values: a = %d, b = %d\n", got, a, b);

  if (got != 2) {
    puts("bad input");
    return 1;                              // always check the return value
  }

  double d = 0;
#ifdef BAD_SCANF
  int got2 = scanf("%f", &d);             // UB: %f wants float *, d is double * → 4 of 8 bytes written
#else
  int got2 = scanf("%lf", &d);            // for double in scanf the specifier is %lf
#endif
  printf("got2 = %d, d = %f\n", got2, d);
  return 0;
}
