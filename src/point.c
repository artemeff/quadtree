#include "quadtree.h"

point_t *
point_new(double x, double y, void *key) {
  point_t* point;
  if (!(point = malloc(sizeof(*point)))) {
    return NULL;
  }
  point->x = x;
  point->y = y;
  point->key = key;
  return point;
}

void
point_free(point_t *point, void (*key_free)(void*)){
    if (key_free != NULL) {
      (*key_free)(point->key);
    }
    free(point);
}
