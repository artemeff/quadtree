#include "benchmark.h"
#include "../src/quadtree.h"

static quadtree_t *tree100k, *tree10m;

void fill_tree_100k() {
  int times = 100000, val = 10;
  double x, y;

  start();
  while(times--) {
    x = (double) (rand() % 1000);
    y = (double) (rand() % 1000);
    quadtree_insert(tree100k, x, y, &val);
  }
  stop();
}

void fill_tree_10m() {
  int times = 10000000, val = 10;
  double x, y;

  start();
  while(times--) {
    x = (double) (rand() % 1000);
    y = (double) (rand() % 1000);
    quadtree_insert(tree10m, x, y, &val);
  }
  stop();
}

void ascent(node_t *node) {}

void descent(node_t *node) {}

void walking_in_tree_100k() {
  start();
  quadtree_walk(tree100k->root, &ascent, &descent);
  stop();
}

void walking_in_tree_10m() {
  start();
  quadtree_walk(tree10m->root, &ascent, &descent);
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

void finds_0_0_200_200_in_tree_100k_walk() {
  node_asc = malloc(sizeof(result_node_t));

  start();
  quadtree_walk(tree100k->root, &ascent_find, &descent);
  stop();
}

void finds_0_0_200_200_in_tree_10m_walk() {
  node_asc = malloc(sizeof(result_node_t));

  start();
  quadtree_walk(tree10m->root, &ascent_find, &descent);
  stop();
}

result_node_t *head, *cur;

void within_cb(point_t *point) {
  cur = malloc(sizeof(result_node_t));
  cur->point = point;
  cur->next  = head;
  head = cur;
}

void finds_0_0_200_200_in_tree_100k_within() {
  bounds_t *bbox = bounds_create(0.0, 0.0, 200.0, 200.0);

  start();
  quadtree_within(tree100k->root, bbox, within_cb);
  stop();
}

void finds_0_0_200_200_in_tree_10m_within() {
  bounds_t *bbox = bounds_create(0.0, 0.0, 200.0, 200.0);

  start();
  quadtree_within(tree10m->root, bbox, within_cb);
  stop();
}

void finds_0_0_15_15_in_tree_100k_within() {
  bounds_t *bbox = bounds_create(0.0, 0.0, 15.0, 15.0);

  start();
  quadtree_within(tree100k->root, bbox, within_cb);
  stop();
}

void finds_0_0_15_15_in_tree_10m_within() {
  bounds_t *bbox = bounds_create(0.0, 0.0, 15.0, 15.0);

  start();
  quadtree_within(tree10m->root, bbox, within_cb);
  stop();
}

int main(){
  b_desc();
  srand(time(NULL));
  tree100k = quadtree_new(0, 0, 1000, 1000);
  tree10m  = quadtree_new(0, 0, 1000, 1000);

  bench(fill_tree_100k);
  bench(walking_in_tree_100k);
  bench(finds_0_0_200_200_in_tree_100k_walk);
  bench(finds_0_0_200_200_in_tree_100k_within);
  bench(finds_0_0_15_15_in_tree_100k_within);

  bench(fill_tree_10m);
  bench(walking_in_tree_10m);
  bench(finds_0_0_200_200_in_tree_10m_walk);
  bench(finds_0_0_200_200_in_tree_10m_within);
  bench(finds_0_0_15_15_in_tree_10m_within);

  quadtree_free(tree100k);
  return b_isok();
}
