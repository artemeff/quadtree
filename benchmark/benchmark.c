#include "benchmark.h"
#include "../src/quadtree.h"

static quadtree_t *tree;

void fill_small_tree() {
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
  if (node && node->point) {
    // ok
  }
}

void descent(node_t *node) {
  if (node && node->point) {
    // ok
  }
}

void walking_in_small_tree() {
  start();
  quadtree_walk(tree->root, &ascent, &descent);
  stop();
}

void ascent_find(node_t *node) {
  if (node && node->point) {
    if (node->point->x >= 0.0 && node->point->x <= 200.0
     && node->point->y >= 0.0 && node->point->y <= 200.0) {
      // ok
    }
  }
}

void finds_0_0_200_200_in_small_tree_walk() {
  start();
  quadtree_walk(tree->root, &ascent_find, &descent);
  stop();
}

void finds_0_0_200_200_in_small_tree_within() {
  bounds_t  *bbox    = bounds_create(0.0, 0.0, 200.0, 200.0);
  results_t *results = (results_t *)malloc(sizeof(results_t));
  results->index = 0;
  results->full = false;

  start();
  quadtree_within(tree->root, bbox, results);
  stop();

  for (int i = 0; i < results->index; i++) {
    printf("%6.20f x %6.20f\n", results->points[i]->x, results->points[i]->x);
  }
}

int main(){
  b_desc();
  srand(time(NULL));
  tree = quadtree_new(0, 0, 1000, 1000);

  bench(fill_small_tree, 0.12);
  bench(walking_in_small_tree, 0.01);
  bench(finds_0_0_200_200_in_small_tree_walk, 0.015);
  bench(finds_0_0_200_200_in_small_tree_within, 0.004);

  quadtree_free(tree);
  return b_isok();
}
