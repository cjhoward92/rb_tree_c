#include "rbtree.h"

int work() {
  return 0;
}

rb_node *new_node(int key) {
  rb_node *node = (rb_node *)malloc(sizeof(rb_node));

  node->left = NULL;
  node->right = NULL;
  node->key = key;
  node->color = RB_TREE_BLACK;

  return node;
}

rb_node *insert_node(int key, rb_node *root) {
  if (!root) {
    return NULL;
  }

  rb_node *next;
  if (root->key == key) {
    next = root;
  }
  else if (root->key < key) {
    next = insert_node(key, root->right);
    if (!next) {
      next = new_node(key);
      next->color = RB_TREE_RED;
      if (root->color == RB_TREE_RED) {

      }
    }
  } else {
    next = insert_node(key, root->left);
    if (!next) {
      next = new_node(key);
      next->color = RB_TREE_RED;
      if (root->color == RB_TREE_RED) {

      }
    }
  }
  return next;
}