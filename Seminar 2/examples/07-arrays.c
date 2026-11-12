// RUN-1: clang -Wall -Wextra 07-arrays.c -o ar7 && ./ar7   // clang also warns [-Warray-bounds]
// RUN-2: gcc -Wall -Wextra 07-arrays.c -o ar7g && ./ar7g   // gcc also warns that f reads 40 bytes from a 16-byte array
// RUN-3: clang -Wall -Wextra -fsanitize=address 07-arrays.c -o ar7asan && ./ar7asan   // the last write is caught

#include <stddef.h>
#include <stdio.h>

void array_param(int a[10]);
void print_array(const int *a, size_t n);

int main(void) {
  int a[5] = {1, 2, 3};                  // missing elements are zeros
  printf("a[3] = %d\n", a[3]);           // 0
  printf("sizeof a = %zu bytes, elements = %zu\n", sizeof a, sizeof a / sizeof a[0]);

  int b[] = {10, 20, 30, 40};
  int *p = b + 1;
  int *q = b + 3;
  printf("*p = %d, q - p = %td, *(q - 1) = %d, p[1] = %d\n", *p, q - p, *(q - 1), p[1]);
  printf("p[1] is *(p + 1) is b[2]: indexing is address arithmetic\n");

  double ad[3] = {1, 2, 3};
  char ac[3] = {1, 2, 3};
  printf("p + 1 moves by sizeof(*p) bytes: int %ld, double %ld, char %ld\n",
         (long)((char *)(b + 1) - (char *)b),
         (long)((char *)(ad + 1) - (char *)ad),
         (long)((char *)(ac + 1) - (char *)ac));

  size_t n = sizeof b / sizeof b[0];
  int sum = 0;
  for (int *r = b; r != b + n; r++)      // b + n is the one-past address: taking it is ok, reading is UB
    sum += *r;
  printf("sum by pointer walk = %d\n", sum);

  print_array(b, n);
  array_param(b);

  a[5] = 6;                              // UB: valid indexes are 0..4, C checks nothing
  printf("plain build prints a[5] = %d\n", a[5]);
  return 0;
}

void array_param(int a[10]) {
  printf("sizeof a inside a function = %zu\n", sizeof a);   // 8: the parameter is really int *a
}

void print_array(const int *a, size_t n) {
  for (size_t i = 0; i < n; i++)
    printf("%d ", a[i]);
  puts("");
}
