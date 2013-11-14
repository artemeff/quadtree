#include "quadtree.h"

point_t *
point_new(double x, double y) {
  point_t* point;
  if(!(point = malloc(sizeof(*point))))
    return NULL;
  point->x = x;
  point->y = y;
  return point;
}

void
point_free(point_t *point){
  free(point);
}
