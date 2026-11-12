// RUN-1: clang -O0 08-unspec.c -o unspec_clang && ./unspec_clang   // prints: f g 3
// RUN-2: gcc -O0 08-unspec.c -o unspec_gcc && ./unspec_gcc         // prints: g f 3
// The order of evaluation of function arguments is unspecified, so both orders are legal.

#include <stdio.h>

int f(void) { printf("f "); return 1; }
int g(void) { printf("g "); return 2; }
void h(int a, int b) { printf("%d ", a + b); }

int main(void) {
    h(f(), g());
}
