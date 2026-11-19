// RUN-1: clang -Wall -Wextra -Wshadow 06-scope-static.c -o s6 && ./s6   // 2 -Wshadow warnings
// RUN-2: clang -Wall -Wextra -DNO_STATIC 06-scope-static.c -o s6ns && ./s6ns   // counter: 1 1 1
// Scope is where a name can be used; storage duration is how long the object lives.

#include <stdio.h>

int x = 1;    // file scope, static duration
int g;        // uninitialized global: guaranteed 0

void counter(void) {
#ifdef NO_STATIC
  int n = 0;            // created on every call
#else
  static int n = 0;     // created once, keeps its value between calls
#endif
  n++;
  printf("%d ", n);
}

int main(void) {
  printf("%d\n", x);        // 1
  int x = 2;                // hides the global x
  {
    int x = 3;              // hides the block x
    printf("%d\n", x);      // 3
  }
  printf("%d\n", x);        // 2: the innermost x no longer exists
  printf("g = %d\n", g);    // 0: an uninitialized local would be garbage
  counter(); counter(); counter();   // 1 2 3, with -DNO_STATIC: 1 1 1
  puts("");
  return 0;
}
