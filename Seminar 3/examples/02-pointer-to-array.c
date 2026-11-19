// RUN-1: clang -Wall -Wextra 02-pointer-to-array.c -o pa2 && ./pa2
// Same address, two types: int * steps by one int, int (*)[5] steps by the whole array.
// Reading a declaration: start at the name, go right, then out of the brackets to the left.
//   int *x[3]   ->  array of 3 pointers      int (*y)[3]  ->  pointer to an array of 3 int

#include <stdio.h>

int main(void) {
  int a[5] = {1, 2, 3, 4, 5};
  printf("a = %p, &a = %p   // the same address\n", (void *)a, (void *)&a);
  printf("a + 1 = %p, &a + 1 = %p   // +4 bytes, +20 bytes\n",
         (void *)(a + 1), (void *)(&a + 1));

  int *p = a;          // int *
  int (*q)[5] = &a;    // int (*)[5]
  printf("sizeof *p = %zu, sizeof *q = %zu\n", sizeof *p, sizeof *q);   // 4, 20
  (*q)[3] = 99;        // *q is the whole array a
  printf("p[3] = %d\n", p[3]);         // 99

  int x = 1, y = 2, z = 3;
  int *ptrs[3] = {&x, &y, &z};         // [ ] binds to the name: array of pointers
  for (int i = 0; i < 3; i++)
    *ptrs[i] += 10;                    // *ptrs[i] is *(ptrs[i])
  printf("x = %d, y = %d, z = %d   // one loop changes three variables\n", x, y, z);

  int r0[] = {1, 2};
  int r1[] = {3, 4, 5, 6};
  int *rows[2] = {r0, r1};             // rows of DIFFERENT lengths
  printf("rows[1][2] = %d\n", rows[1][2]);   // 5: rows[1] is r1, then a normal [2]

  return 0;
}
