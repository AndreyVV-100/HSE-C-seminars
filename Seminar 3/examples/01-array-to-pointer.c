// RUN-1: clang -Wall -Wextra 01-array-to-pointer.c -o a1 && ./a1
// RUN-2: gcc -Wall -Wextra 01-array-to-pointer.c -o a1g && ./a1g
// In an expression an array becomes a pointer to its first element.
// a[i] is *(a + i); indexing is address arithmetic.

#include <stdio.h>

int main(void) {
  int a[5] = {1, 2, 3};                 // missing elements are zeros
  printf("a[3] = %d, sizeof a = %zu, sizeof a / sizeof a[0] = %zu\n",
         a[3], sizeof a, sizeof a / sizeof a[0]);   // 0, 20 bytes, 5 elements

  int b[3] = {10, 20, 30};
  int *p = b;
  printf("*p + 1 = %d, *(p + 1) = %d\n", *p + 1, *(p + 1));   // 11, 20: * binds tighter than +
  printf("p[1] = %d, *(b + 2) = %d\n", p[1], *(b + 2));       // 20, 30

  printf("p + 1 is %p, p is %p: a step is sizeof(int) = %zu bytes\n",
         (void *)(p + 1), (void *)p, sizeof(int));

  int c[3], d[3];
  int *u = c, *v = d;
  printf("u == v: %d   // == is legal for any two pointers\n", u == v);
  printf("u < v: %d, v - u: %td   // UB: the arrays' relative position is unknown\n",
         u < v, v - u);               // clang 0 and -3, gcc 1 and 3

  return 0;
}
