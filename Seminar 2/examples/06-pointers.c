// RUN-1: clang -Wall -Wextra 06-pointers.c -o p6 && ./p6
// RUN-2: gcc -Wall -Wextra 06-pointers.c -o p6g && ./p6g
// RUN-3: clang -Wall -Wextra -DNULL_DEREF 06-pointers.c -o p6null && ./p6null     // segfault, exit 139
// RUN-4: clang -Wall -Wextra -DUNINIT_DEREF 06-pointers.c -o p6uninit && ./p6uninit // segfault, exit 139
// RUN-5: clang -Wall -Wextra -DBOGUS_DEREF 06-pointers.c -o p6bogus && ./p6bogus    // segfault, exit 139
// The three defines dereference: NULL, an uninitialized pointer, a random address. All are UB.
// On our machine all three crash; a garbage address can also corrupt memory silently.

#include <stdio.h>

void swap_by_value(int a, int b);
void swap_by_pointer(int *a, int *b);

int main(void) {
#if defined(NULL_DEREF) || defined(UNINIT_DEREF) || defined(BOGUS_DEREF)
  int *bad;
#ifdef NULL_DEREF
  bad = NULL;                                   // declared and initialized to NULL
  printf("dereferencing NULL:\n");
#elif defined(UNINIT_DEREF)
  printf("dereferencing an uninitialized pointer:\n");   // -Wuninitialized: the address is stack garbage
  /* bad is never assigned: it holds whatever was in that memory */
#else
  bad = (int *)0x12345678UL;                  // a random address that is not ours
  printf("dereferencing a bogus address 0x12345678:\n");
#endif
  fflush(stdout);
  *bad = 5;                                     // UB: the program crashes here
  puts("never printed");
  return 0;
#else
  int x = 5;
  int *p = &x;                                  // p stores the address of x
  printf("x = %d lives at %p\n", x, (void *)&x);
  printf("p stores %p\n", (void *)p);
  printf("sizeof(int) = %zu, sizeof(int *) = %zu, sizeof(double *) = %zu\n",
         sizeof(int), sizeof(int *), sizeof(double *));   // pointer size is not the object size

  *p = 10;                                      // * in an expression: write through the pointer
  x++;
  printf("x = %d, *p = %d\n", x, *p);          // 11 11: x and *p are the same object

  int a = 1, b = 2;
  swap_by_value(a, b);
  printf("swap by value:   %d %d\n", a, b);    // 1 2: only the copies were swapped
  swap_by_pointer(&a, &b);
  printf("swap by pointer: %d %d\n", a, b);    // 2 1: this is why scanf needs &
  return 0;
#endif
}

void swap_by_value(int a, int b) {
  int t = a;
  a = b;
  b = t;
}

void swap_by_pointer(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}
