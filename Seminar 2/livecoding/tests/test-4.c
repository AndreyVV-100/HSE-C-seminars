// Тест 4 (план, 3.4): общий сосед и цикл — A->left = B, A->right = C, B->right = C, C->left = A.
// Тот же free_tree: ветка через B освобождает C, ветка A->right читает освобождённый C.  Рисунок: test-4.dot
#include "../graph.h"

struct node *build(void) {
  struct node *a = new_node(1);
  struct node *b = new_node(2);
  struct node *c = new_node(3);
  a->left  = b;
  a->right = c;
  b->right = c;
  c->left  = a;
  return a;
}
