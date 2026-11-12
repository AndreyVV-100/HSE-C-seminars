// Тест 2 (план, 3.2): три вершины — корень с left и right.  Рисунок: test-2.dot
#include "../graph.h"

struct node *build(void) {
  struct node *root = new_node(1);
  root->left  = new_node(2);
  root->right = new_node(3);
  return root;
}
