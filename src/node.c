#include "quadtree.h"

int
node_ispointer(node_t *node){
  return node->nw != NULL
      && node->ne != NULL
      && node->sw != NULL
      && node->se != NULL
      && !node_isleaf(node);
}

int
node_isempty(node_t *node){
  return node->nw == NULL
      && node->ne == NULL
      && node->sw == NULL
      && node->se == NULL
      && !node_isleaf(node);
}

int
node_isleaf(node_t *node){
  return node->point != NULL;
}

void
node_reset(node_t* node, void (*key_free)(void*)) {
  if(node->point)
    point_free(node->point, key_free);
}

node_t *
node_new() {
  node_t *node;
  if (!(node = malloc(sizeof(*node)))) {
    return NULL;
  }
  node->ne     = NULL;
  node->nw     = NULL;
  node->se     = NULL;
  node->sw     = NULL;
  node->point  = NULL;
  node->bounds = NULL;
  return node;
}

node_t *
node_with_bounds(double minx, double miny, double maxx, double maxy){
  node_t* node;
  if (!(node = node_new())) return NULL;
  if (!(node->bounds = bounds_new())) return NULL;
  bounds_extend(node->bounds, maxx, maxy);
  bounds_extend(node->bounds, minx, miny);
  return node;
}

void
node_free(node_t* node, void (*key_free)(void*)) {
  if (node->nw != NULL) node_free(node->nw, key_free);
  if (node->ne != NULL) node_free(node->ne, key_free);
  if (node->sw != NULL) node_free(node->sw, key_free);
  if (node->se != NULL) node_free(node->se, key_free);

  bounds_free(node->bounds);
  node_reset(node, key_free);
  free(node);
}
