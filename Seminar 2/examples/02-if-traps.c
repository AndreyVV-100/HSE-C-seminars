// RUN-1: clang -Wall -Wextra 02-if-traps.c -o if2 && ./if2
// RUN-2: gcc -Wall -Wextra 02-if-traps.c -o if2g && ./if2g
// -Wall catches the assignment in if, -Wextra catches the dangling else and the empty body.
// Without the flags the program compiles and prints a surprising result.

#include <stdio.h>

int main(void) {
  int x = 0;
  if (x = 1)                 // assignment, not comparison: value is 1, so the branch is taken
    puts("x is 1");          // -Wall: suggest parentheses around assignment used as truth value
  else
    puts("x is not 1");
  printf("x = %d\n", x);     // x is really 1 now

  int a = 1, b = 0;
  if (a)
    if (b)
      puts("A");
  else
    puts("B");               // else belongs to the nearest if: prints B, indentation is a lie

  int y = 3;
  if (y > 10);               // the ; is an empty statement: it is the whole body of the if
  {
    puts("big");             // this block is a separate statement, it always runs
  }
  return 0;
}
