#include "rbtree.h"

static void print(const rb_node *node, int depth) {
  if (!node) {
    return;
  }

  print(node->left, depth + 1);
  printf(
    "(Key: %d; %s; P: %d)",
    node->key,
    node->color ? "B" : "R",
    node->parent ? node->parent->key : 0
  );
  print(node->right, depth + 1);
} 

static int is_red(const rb_node *node) {
  if (!node)
    return 0;
  
  return node->color;
}

static int is_root(const rb_node *node) {
  if (!node)
    return 0;

  if (!node->parent)
    return 1;
  return 0;
}

static int is_left(const rb_node *node) {
  if (!node || !node->parent)
    return 0;
  
  if (node->parent->left == node)
    return 1;
  return 0;
}

static rb_node *get_uncle(const rb_node *node) {
  if (!node || !node->parent || !node->parent->parent)
    return NULL;
  
  rb_node *gp = node->parent->parent;
  if (gp->left == node->parent)
    return gp->right;
  return gp->left;
}

static void flip_color(rb_node *node) {
  if (!node)
    return;

  node->color = node->color == RB_TREE_BLACK ? RB_TREE_RED : RB_TREE_BLACK;
}

static void rotate_left(rb_node *node, int swap_colors) {
  rb_node *right = node->right;
  right->parent = node->parent;
  node->right = right->left;
  right->left = node;
  node->parent = right;

  if (swap_colors) {
    flip_color(node);
    flip_color(right);
  }
}

static void rotate_right(rb_node *node, int swap_colors) {
  rb_node *left = node->left;
  left->parent = node->parent;
  node->left = left->right;
  left->right = node;
  node->parent = left;

  if (swap_colors) {
    flip_color(node);
    flip_color(left);
  }
}

static void balance_tree(rb_node *node) {
  if (!node)
    return;

  if (is_root(node)) {
    node->color = RB_TREE_BLACK;
    return;
  }

  if (is_red(get_uncle(node))) {
    node->parent->parent->left->color = RB_TREE_BLACK;
    node->parent->parent->color = RB_TREE_RED;
    node->parent->parent->right->color = RB_TREE_BLACK;
    balance_tree(node->parent->parent);
    return;
  }

  if (!is_red(node->parent))
    return;

  if (is_left(node->parent)) {
    if (is_left(node)) {
      rotate_right(node->parent->parent, 1);
    } else {
      rotate_left(node->parent, 0);
      rotate_right(node->parent, 1);
    }
  }

  if (is_left(node)) {
    rotate_right(node->parent, 0);
    rotate_left(node->parent, 1);
  }

  rotate_left(node->parent->parent, 1);
}

rb_node *new_node(int key) {
  rb_node *node = (rb_node *)malloc(sizeof(rb_node));

  node->left = NULL;
  node->right = NULL;
  node->parent = NULL;
  node->key = key;
  node->color = RB_TREE_BLACK;

  return node;
}

void insert_node(int key, rb_node *root) {
  if (!root) {
    return;
  }

  if (key >= root->key) {
    if (!root->right) {
      root->right = new_node(key);
      root->right->color = RB_TREE_RED;
      root->right->parent = root;
      balance_tree(root->right);
    } else {
      insert_node(key, root->right);
    }
  } else {
    if (!root->left) {
      root->left = new_node(key);
      root->left->color = RB_TREE_RED;
      root->left->parent = root;
      balance_tree(root->left);
    } else {
      insert_node(key, root->left);
    }
  }
}

rb_node *find_node(int key, const rb_node *root) {
  if (!root) {
    return NULL;
  }

  if (root->key <= key) {
    return find_node(key, root->right);
  }

  return find_node(key, root->left);
}

void free_tree(rb_node *node) {
  if (!node) {
    return;
  }

  free_tree(node->left);
  free_tree(node->right);
  node->parent = NULL;
  free(node);
}

void print_tree(const rb_node *root) {
  print(root, 0);
}