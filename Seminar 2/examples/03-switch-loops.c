// RUN-1: clang -Wall -Wextra 03-switch-loops.c -o sw3 && ./sw3
// RUN-2: gcc -Wall -Wextra 03-switch-loops.c -o sw3g && ./sw3g   // -Wextra catches the fallthrough
// case is only a label: without break execution continues into the next case.

#include <stdio.h>

int main(void) {
  int n = 1;
  switch (n) {
    case 1: printf("one ");     // no break: falls through
    case 2: printf("two ");
    default: printf("other ");
  }
  puts("");                     // prints: one two other

  for (int i = 0; i < 10; i++) {
    if (i % 2 != 0)
      continue;                // skip odd: go to i++ first
    if (i > 6)
      break;                   // leave the loop at i = 8
    printf("%d ", i);
  }
  puts("");                     // prints: 0 2 4 6

  int a = 0, b = 0, c = 0, k = 10;
  for (int i = 0; i < 10; i += 3) a++;        // i = 0, 3, 6, 9: 4 passes
  do { b++; k++; } while (k < 5);             // condition is false, body still runs once
  while (0) c++;                              // never runs
  printf("loop bodies: %d %d %d\n", a, b, c);  // 4 1 0
  return 0;
}
