// graph.c — один main: вызов билдера из теста, печать корня, попытка освободить граф.
// Сборка вместе с тестом: clang -g -Wall -Wextra -fsanitize=address graph.c test-1.c -o test-1
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct node *build(void);        // каждый тест определяет свою функцию сборки
void free_tree(struct node *n);  // каждый тест определяет свою функцию освобождения

struct node *new_node(int value) {
  struct node *n = malloc(sizeof *n);
  if (n == NULL) {
    perror("malloc");
    exit(1);
  }
  n->value = value;
  n->left = NULL;
  n->right = NULL;
  return n;
}

int main(void) {
  struct node *a = build();
  printf("node at %p: value = %d, left = %p, right = %p\n",
         (const void *)a, a->value, (const void *)a->left, (const void *)a->right);
  free_tree(a);
  return 0;
}
