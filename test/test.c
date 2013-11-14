#include "test.h"
#include "../src/quadtree.h"

void test_node() {
  node_t *node = node_new();
  assert(!node_isleaf(node));
  assert(node_isempty(node));
  assert(!node_ispointer(node));
}

void test_bounds() {
  bounds_t *bounds = bounds_new();

  assert(bounds->nw->x == INFINITY);
  assert(bounds->se->x == -INFINITY);

  bounds_extend(bounds, 5.0, 5.0);
  assert(bounds->nw->x == 5.0);
  assert(bounds->se->x == 5.0);

  bounds_extend(bounds, 10.0, 10.0);
  assert(bounds->nw->y == 10.0);
  assert(bounds->nw->y == 10.0);
  assert(bounds->se->y == 5.0);
  assert(bounds->se->y == 5.0);

  assert(bounds->width == 5.0);
  assert(bounds->height == 5.0);

  bounds_free(bounds);
}

/**
 * walking callbacks
 */
static int asc_size = 0, desc_size = 0;

void ascent(node_t *node) {
  if (node && node->point && node->point->x) {
    asc_size++;
  }
}

void descent(node_t *node) {
  if (node && node->point && node->point->x) {
    desc_size++;
  }
}

void test_walking() {
  int i, val = 10;
  quadtree_t *tree = quadtree_new(0, 0, 100, 100);

  for (i = 1; i < 30; i++) {
    quadtree_insert(tree, (double) i, (double) i, &val);
  }

  quadtree_walk(tree->root, &ascent, &descent);

  assert(tree->length == asc_size);
  assert(tree->length == desc_size);

  quadtree_free(tree);
}

void test_tree() {
  int val = 10;

  quadtree_t *tree = quadtree_new(1, 1, 10, 10);
  assert(tree->root->bounds->nw->x == 1);
  assert(tree->root->bounds->nw->y == 10.0);
  assert(tree->root->bounds->se->x == 10.0);
  assert(tree->root->bounds->se->y == 1);


  assert(quadtree_insert(tree, 0, 0, &val) == 0);
  assert(quadtree_insert(tree, 10, 10, &val) == 0);
  assert(quadtree_insert(tree, 110.0, 110.0, &val) == 0);

  assert(quadtree_insert(tree, 8.0, 2.0, &val) != 0);
  assert(tree->length == 1);
  assert(tree->root->point->x == 8.0);
  assert(tree->root->point->y == 2.0);

  assert(quadtree_insert(tree, 2.0, 3.0, &val) != 0);
  assert(quadtree_insert(tree, 2.0, 3.0, &val) == 0);
  assert(tree->length == 2);
  assert(tree->root->point == NULL);

  assert(quadtree_insert(tree, 3.0, 1.1, &val) == 1);
  assert(tree->length == 3);
  assert(quadtree_search(tree, 3.0, 1.1)->x == 3.0);
  quadtree_free(tree);
}

void test_points() {
  point_t *point = point_new(5, 6);
  assert(point->x == 5);
  assert(point->y == 6);
  point_free(point);
}

void test_search() {
  pending("everything fine");
}

int main() {
  case(test_points);
  case(test_node);
  case(test_bounds);
  case(test_walking);
  case(test_tree);
  case(test_search);

  return t_isok();
}
