#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef unsigned int uint;

typedef struct point {
  double x;
  double y;
  void  *key;
} point_t;

typedef struct bounds {
  point_t *nw;
  point_t *se;
  double   width;
  double   height;
} bounds_t;

typedef struct node {
  struct node *ne;
  struct node *nw;
  struct node *se;
  struct node *sw;
  bounds_t    *bounds;
  point_t     *point;
  //void        *key;
} node_t;

typedef struct quadtree {
  node_t *root;
  void  (*key_free)(void *key);
  uint    length;
} quadtree_t;

typedef struct result_node {
  struct result_node *next;
  point_t            *point;
} result_node_t;

typedef void (*within_callback_t)(point_t *point);
point_t*    point_new(double x, double y, void* key);
void        point_free(point_t *point, void (*key_free)(void*));
bounds_t*   bounds_new();
bounds_t*   bounds_create(double x1, double y1, double x2, double y2);
void        bounds_extend(bounds_t *bounds, double x, double y);
void        bounds_free(bounds_t *bounds);
bool        bounds_intersect(bounds_t *bbox, node_t *node);
node_t*     node_new();
void        node_free(node_t *node, void (*key_free)(void*));
int         node_ispointer(node_t *node);
int         node_isempty(node_t *node);
int         node_isleaf(node_t *node);
void        node_reset(node_t* node, void (*key_free)(void*));
node_t*     node_with_bounds(double minx, double miny, double maxx, double maxy);
quadtree_t* quadtree_new(double minx, double miny, double maxx, double maxy);
void        quadtree_free(quadtree_t *tree);
point_t*    quadtree_search(quadtree_t *tree, double x, double y);
point_t*    quadtree_insert(quadtree_t *tree, double x, double y, void *key, bool update);
void        quadtree_within(node_t *tree, bounds_t *bounds, within_callback_t cb);
void        quadtree_walk(node_t *root,
                          void (*descent)(node_t *node),
                          void (*ascent)(node_t *node));

#endif
