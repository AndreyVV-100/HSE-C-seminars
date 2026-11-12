#include <stdio.h>

int f(void) { printf("f "); return 1; }
int g(void) { printf("g "); return 2; }
void h(int a, int b) { printf("%d ", a + b); }

int main(void) {
    h(f(), g());
}
