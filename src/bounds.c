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
bounds_free(bounds_t *bounds) {
  point_free(bounds->nw, NULL);
  point_free(bounds->se, NULL);
  free(bounds);
}

bounds_t*
bounds_new() {
  bounds_t *bounds;
  if ((bounds = malloc(sizeof(*bounds))) == NULL) {
    return NULL;
  }
  bounds->nw     = point_new(INFINITY, -INFINITY, NULL);
  bounds->se     = point_new(-INFINITY, INFINITY, NULL);
  bounds->width  = 0;
  bounds->height = 0;
  return bounds;
}

bounds_t*
bounds_create(double x1, double y1, double x2, double y2) {
  bounds_t *bounds;
  if ((bounds = malloc(sizeof(*bounds))) == NULL) {
    return NULL;
  }
  bounds->nw     = point_new(x1, y1, NULL);
  bounds->se     = point_new(x2, y2, NULL);
  bounds->width  = fabs(bounds->nw->x - bounds->se->x);
  bounds->height = fabs(bounds->nw->y - bounds->se->y);
  return bounds;
}

bool
bounds_intersect(bounds_t *bbox, node_t *node) {
  double d1 = bbox->se->x - bbox->nw->x;
  double d2 = node->bounds->nw->x - bbox->se->x;
  double d3 = node->bounds->se->x - node->bounds->nw->x;
  double d4 = bbox->nw->x - node->bounds->se->x;

  if (d1 < 0) d1 += 360;
  if (d2 < 0) d2 += 360;
  if (d3 < 0) d3 += 360;
  if (d4 < 0) d4 += 360;

  return ((d1 + d2 + d3 + d4) != 360);
}
