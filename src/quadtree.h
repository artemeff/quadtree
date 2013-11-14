#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <stdlib.h>
#include <math.h>

typedef unsigned int uint;

typedef struct point {
  double x, y;
} point_t;

typedef struct bounds {
  point_t *nw;
  point_t *se;
  double width;
  double height;
} bounds_t;

typedef struct node {
  struct node *ne;
  struct node *nw;
  struct node *se;
  struct node *sw;
  bounds_t *bounds;
  point_t  *point;
  void *key;
} node_t;

typedef struct quadtree {
  node_t *root;
  void  (*key_free)(void *key);
  uint    length;
} quadtree_t;


point_t*    point_new(double x, double y);
void        point_free(point_t *point);
bounds_t*   bounds_new();
void        bounds_extend(bounds_t *bounds, double x, double y);
void        bounds_free(bounds_t *bounds);
node_t*     node_new();
void        node_free(node_t *node, void (*value_free)(void*));
int         node_ispointer(node_t *node);
int         node_isempty(node_t *node);
int         node_isleaf(node_t *node);
void        node_reset(node_t* node, void (*key_free)(void*));
node_t*     node_with_bounds(double minx, double miny, double maxx, double maxy);
quadtree_t* quadtree_new(double minx, double miny, double maxx, double maxy);
void        quadtree_free(quadtree_t *tree);
point_t*    quadtree_search(quadtree_t *tree, double x, double y);
int         quadtree_insert(quadtree_t *tree, double x, double y, void *key);
void        quadtree_walk(node_t *root,
                 void (*descent)(node_t *node),
                 void (*ascent)(node_t *node));

#endif
