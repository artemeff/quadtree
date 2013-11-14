#include "quadtree.h"

void
bounds_extend(bounds_t *bounds, double x, double y){
  bounds->nw->x  = fmin(x, bounds->nw->x);
  bounds->nw->y  = fmax(y, bounds->nw->y);
  bounds->se->x  = fmax(x, bounds->se->x);
  bounds->se->y  = fmin(y, bounds->se->y);
  bounds->width  = fabs(bounds->nw->x - bounds->se->x);
  bounds->height = fabs(bounds->nw->y - bounds->se->y);
}

void
bounds_free(bounds_t *bounds){
  point_free(bounds->nw);
  point_free(bounds->se);
  free(bounds);
}

bounds_t*
bounds_new(){
  bounds_t *bounds;
  if((bounds = malloc(sizeof(*bounds))) == NULL)
    return NULL;
  bounds->nw     = point_new(INFINITY, -INFINITY);
  bounds->se     = point_new(-INFINITY, INFINITY);
  bounds->width  = 0;
  bounds->height = 0;
  return bounds;
}
