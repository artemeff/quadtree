#include "benchmark.h"
#include "../src/quadtree.h"

static quadtree_t *tree;

void fill_tree_100000() {
  int times = 100000, val = 10;
  double x, y;

  start();
  while(times--){
    x = (double) (rand() % 1000);
    y = (double) (rand() % 1000);
    quadtree_insert(tree, x, y, &val);
  }
  stop();
}

void ascent(node_t *node) {}

void descent(node_t *node) {}

void walking_in_tree_100000() {
  start();
  quadtree_walk(tree->root, &ascent, &descent);
  stop();
}

result_node_t *node_asc;

void ascent_find(node_t *node) {
  if (node && node->point) {
    if (node->point->x >= 0.0 && node->point->x <= 200.0
     && node->point->y >= 0.0 && node->point->y <= 200.0) {
      result_node_t *next = (result_node_t *)malloc(sizeof(result_node_t));
      node_asc->point = node->point;
      node_asc->next = next;
      node_asc = next;
    }
  }
}

void finds_0_0_200_200_in_tree_100000_walk() {
  node_asc = (result_node_t *)malloc(sizeof(result_node_t));

  start();
  quadtree_walk(tree->root, &ascent_find, &descent);
  stop();
}

result_node_t *head, *cur;

void within_cb(point_t *point) {
  cur = (result_node_t *)malloc(sizeof(result_node_t));
  cur->point = point;
  cur->next  = head;
  head = cur;
}

void finds_0_0_200_200_in_tree_100000_within() {
  bounds_t *bbox = bounds_create(0.0, 0.0, 200.0, 200.0);

  start();
  quadtree_within(tree->root, bbox, within_cb);
  stop();
}

void finds_0_0_15_15_in_tree_100000_within() {
  bounds_t *bbox = bounds_create(0.0, 0.0, 15.0, 15.0);

  start();
  quadtree_within(tree->root, bbox, within_cb);
  stop();
}

int main(){
  b_desc();
  srand(time(NULL));
  tree = quadtree_new(0, 0, 1000, 1000);

  bench(fill_tree_100000, 0.125);
  bench(walking_in_tree_100000, 0.01);
  bench(finds_0_0_200_200_in_tree_100000_walk, 0.011);
  bench(finds_0_0_200_200_in_tree_100000_within, 0.0045);
  bench(finds_0_0_15_15_in_tree_100000_within, 0.0005);

  quadtree_free(tree);
  return b_isok();
}
