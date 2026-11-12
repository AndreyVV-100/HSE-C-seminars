// Тест 3 (план, 3.3): цикл — A->left = B, B->left = A.  Тот же free_tree: бесконечная рекурсия.
// Рисунок: test-3.dot
#include "../graph.h"

struct node *build(void) {
  struct node *a = new_node(1);
  struct node *b = new_node(2);
  a->left = b;
  b->left = a;
  return a;
}
