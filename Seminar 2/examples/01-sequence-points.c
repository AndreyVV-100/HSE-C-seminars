// RUN-1: clang -Wall -Wextra 01-sequence-points.c -o sp1 && ./sp1
// RUN-2: gcc -Wall -Wextra 01-sequence-points.c -o sp1g && ./sp1g
// A side effect is when an expression produces a value AND changes state (assignment, ++, output).
// Legal forms below have a fixed result. Modifying the same variable twice between two
// sequence points is UB: the two compilers print different numbers.

#include <stdio.h>

int tracked(int x);

int main(void) {
  int i = 5;
  int a = i++;             // value of i++ is the OLD i
  int b = ++i;             // value of ++i is the NEW i
  printf("i++ / ++i:  a = %d, b = %d, i = %d\n", a, b, i);   // 5 7 7

  int j = (i++, i++);      // ok: the comma operator puts a sequence point after its left operand
  printf("comma op:     j = %d, i = %d\n", j, i);            // 8 9

  int k = tracked(1) + tracked(2);   // the sum is 3, the order of the calls is unspecified
  printf("calls:  k = %d\n", k);

  int x = 5;
  x = x++;                 // UB: x is modified and read in one expression
  printf("x = x++:      x = %d\n", x);            // observed: clang 5, gcc 5

  int m = 5;
  int n = m++ + m++;       // UB
  printf("m++ + m++:    n = %d, m = %d\n", n, m); // observed: clang 11 7, gcc 11 7

  int q = 5;
  int r = q * ++q;         // UB
  printf("q * ++q:      r = %d, q = %d\n", r, q); // observed: clang 30 6, gcc 36 6

  int s = 5;
  printf("printf args:  %d %d\n", s, s++);        // UB: commas in printf(...) are argument separators,
  printf("s = %d\n", s);                          // not the comma operator, no sequence point
                                                  // observed: clang "5 5", gcc "6 5"
  return 0;
}

int tracked(int x) {
  printf("tracked(%d) ", x);   // side effect: output
  return x;
}
