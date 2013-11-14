#include "benchmark.h"
#include "../src/quadtree.h"

void mark_insert() {
  int n = 100000;
  int val = 10;
  quadtree_t *tree = quadtree_new(0, 0, 1000, 1000);
  double x;
  double y;
  start();
  while(n--){
    x = (double) (rand() % 1000);
    y = (double) (rand() % 1000);
    quadtree_insert(tree, x, y, &val);
  }
  stop();
  // printf("  %18s %i\n", "length:", tree->length);
  quadtree_free(tree);
}

int main(){
  srand(time(NULL));
  bench(mark_insert, 0.2);

  return b_isok();
}
