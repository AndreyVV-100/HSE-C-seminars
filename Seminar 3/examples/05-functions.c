// RUN-1: clang -Wall -Wextra 05-functions.c -o f5 && ./f5
// RUN-2: clang -Wall -Wextra -DSTAR_STAR 05-functions.c -o f5ss && ./f5ss   // warning, then segfault
// RUN-3: gcc -Wall -Wextra -DSTAR_STAR 05-functions.c -o f5ssg             // the same code: gcc refuses to compile
// The parameter is a copy of the argument; to change the argument, pass its address.
// An array is passed as pointer + length: sizeof inside the function is the pointer size.
// clang warns -Wunused-but-set-parameter for inc: that is the point of inc(a) not changing a.

#include <stddef.h>
#include <stdio.h>

void inc(int x) { x++; }        // the copy is changed
void inc_at(int *x) { (*x)++; } // (*x)++, not *x++: brackets matter

int sum(const int *a, size_t n) {  // const: the function promises not to write
  printf("in sum: sizeof a = %zu, n = %zu   // a is a pointer, not the array\n",
         sizeof a, n);             // 8
  int s = 0;
  for (size_t i = 0; i < n; i++)
    s += a[i];
  return s;
}

int main(void) {
  int a = 5;
  inc(a);        printf("inc(a):     a = %d\n", a);    // 5: only the copy was changed
  inc_at(&a);    printf("inc_at(&a): a = %d\n", a);    // 6: we wrote through the address

  int arr[5] = {1, 2, 3, 4, 5};
  printf("sum(arr, 5) = %d\n", sum(arr, 5));           // 15

  return 0;
}
