// RUN-1: clang -Wall -Wextra 04-vla.c -o v4 && printf '5\n' | ./v4   // sizeof a = 20, a[2] = 2
// RUN-2: clang -Wall -Wextra -DTRY_INIT 04-vla.c -o v4i   // error: variable-sized object may not be initialized
//          gcc says the same: "variable-sized object may not be initialized except with an empty initializer"
// RUN-3: clang -Wall -Wextra -DBIG 04-vla.c -o v4b && printf '5\n' | ./v4b   // segfault at the call, exit 139
// RUN-4: clang -Wall -Wextra -fsanitize=address -DBIG 04-vla.c -o v4asan && printf '5\n' | ./v4asan  // ASan: stack-overflow
// VLA: the size is known only at run time, so sizeof is computed at run time too.

#include <stdio.h>

void big_alloc(int n);

int main(void) {
  int n;
  scanf("%d", &n);          // the size comes from the input
  int a[n];                 // VLA
  printf("sizeof a = %zu\n", sizeof a);     // 4 * n
  for (int i = 0; i < n; i++)
    a[i] = i;               // no initializer: filled by hand
  printf("a[2] = %d\n", a[2]);

#ifdef TRY_INIT
  int b[n] = {0};           // compile error: initializers need a compile-time size
#endif

#ifdef BIG
  fflush(stdout);
  puts("calling big_alloc(1000000000): 4000000000 bytes of stack");
  fflush(stdout);
  big_alloc(1000000000);    // the stack is a few MB: the program dies inside the call
#endif

  return 0;
}

void big_alloc(int n) {
  int huge[n];              // VLA in a function: the frame is built on entry
  huge[0] = 1;              // the array is used, so the memory really gets touched
  printf("never printed\n");
}
