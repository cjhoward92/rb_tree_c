#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"

int main() {
  rb_node *root = new_node(10);

  insert_node(11, root);
  insert_node(5, root);
  insert_node(8, root);
  insert_node(30, root);
  insert_node(15, root);
  insert_node(2, root);

  print_tree(root);

  return 0;
}