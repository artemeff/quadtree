#include "benchmark.h"
#include "../src/quadtree.h"

static quadtree_t *tree;

void insert_100000_times() {
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

void ascent(node_t *node) {
  if (node && node->point && node->point->x) {
    // ok
  }
}

void descent(node_t *node) {
  if (node && node->point && node->point->x) {
    // ok
  }
}

void walking_in_tree_with_100000_points() {
  start();
  quadtree_walk(tree->root, &ascent, &descent);
  stop();
}

int main(){
  srand(time(NULL));
  tree = quadtree_new(0, 0, 1000, 1000);

  bench(insert_100000_times, 0.15);
  bench(walking_in_tree_with_100000_points, 0.015);

  quadtree_free(tree);
  return b_isok();
}
