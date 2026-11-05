// RUN: clang -Wall -Wextra -Werror 01-hello-world.c -o 01-hello-world

#include <stdio.h>

int main(void) {
  printf("Hello, world!\n");
  return 0;
}
