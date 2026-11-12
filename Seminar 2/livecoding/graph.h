#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

// Каркас графа: у узла значение и два указателя на соседей.
struct node {
  int value;
  struct node *left, *right;
};

struct node *new_node(int value);

#endif
