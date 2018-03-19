#ifndef __RB_TREE__
#define __RB_TREE__

#include <stdlib.h>

enum { RB_TREE_BLACK, RB_TREE_RED } RB_COLORS;

typedef struct rb_node {
  struct rb_node *left;
  struct rb_node *right;
  int key;
  int color;
} rb_node;

int work();

rb_node *new_node(int key);
rb_node *insert_node(int key, rb_node *root);
void find_node(int key, const rb_node *root);
void swap_left(rb_node *parent);
void swap_right(rb_node *parent);
void remove_node(rb_node *root);
void free_tree(rb_node *root);

#endif