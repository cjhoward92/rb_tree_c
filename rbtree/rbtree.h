#ifndef __RB_TREE__
#define __RB_TREE__

#include <stdio.h>
#include <stdlib.h>

enum { RB_TREE_BLACK, RB_TREE_RED } RB_COLORS;

typedef struct rb_node {
  struct rb_node *left;
  struct rb_node *right;
  struct rb_node *parent;
  int key;
  int color;
} rb_node;

rb_node *new_node(int key);
void insert_node(int key, rb_node *root);
rb_node *find_node(int key, const rb_node *root);
void remove_node(rb_node *root);

void print_tree(const rb_node *root);
void free_tree(rb_node *root);

#endif