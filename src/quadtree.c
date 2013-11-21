#include "quadtree.h"

/*
** Private prototypes
*/
static bool
split_node_(quadtree_t *tree, node_t *node);

static bool
insert_(quadtree_t* tree, node_t *root, point_t *point, void *key);

static bool
node_contains_(node_t *outer, point_t *it);

static node_t *
get_quadrant_(node_t *root, point_t *point);

/*
** Private implementations
*/
static bool
node_contains_(node_t *outer, point_t *it) {
  return outer->bounds != NULL
      && outer->bounds->nw->x < it->x
      && outer->bounds->nw->y > it->y
      && outer->bounds->se->x > it->x
      && outer->bounds->se->y < it->y;
}

static void
elision_(void* key){}

static void
reset_node_(quadtree_t *tree, node_t *node){
  if(tree->key_free != NULL) {
    node_reset(node, tree->key_free);
  } else {
    node_reset(node, elision_);
  }
}

static node_t *
get_quadrant_(node_t *root, point_t *point) {
  if (node_contains_(root->nw, point)) return root->nw;
  if (node_contains_(root->ne, point)) return root->ne;
  if (node_contains_(root->sw, point)) return root->sw;
  if (node_contains_(root->se, point)) return root->se;
  return NULL;
}


static bool
split_node_(quadtree_t *tree, node_t *node){
  node_t *nw;
  node_t *ne;
  node_t *sw;
  node_t *se;

  double x  = node->bounds->nw->x;
  double y  = node->bounds->nw->y;
  double hw = node->bounds->width / 2;
  double hh = node->bounds->height / 2;

                             //minx, miny,       maxx,       maxy
  if(!(nw = node_with_bounds(x,      y - hh,     x + hw,     y))) return 0;
  if(!(ne = node_with_bounds(x + hw, y - hh,     x + hw * 2, y))) return 0;
  if(!(sw = node_with_bounds(x,      y - hh * 2, x + hw,     y - hh))) return 0;
  if(!(se = node_with_bounds(x + hw, y - hh * 2, x + hw * 2, y - hh))) return 0;

  node->nw = nw;
  node->ne = ne;
  node->sw = sw;
  node->se = se;

  point_t *old = node->point;
  void *key    = node->key;
  node->point  = NULL;
  node->key    = NULL;

  return insert_(tree, node, old, key);
}


static point_t*
find_(node_t* node, double x, double y) {
  if(node_isleaf(node)) {
    if(node->point->x == x && node->point->y == y)
      return node->point;
  } else {
    point_t test;
    test.x = x;
    test.y = y;
    return find_(get_quadrant_(node, &test), x, y);
  }

  return NULL;
}

static bool
insert_(quadtree_t* tree, node_t *root, point_t *point, void *key) {
  if (node_isempty(root)) {
    root->point = point;
    root->key   = key;
    return true;
  } else if (node_isleaf(root)) {
    if (root->point->x == point->x && root->point->y == point->y) {
      reset_node_(tree, root);
      root->point = point;
      root->key   = key;
      return false;
    } else {
      if (!split_node_(tree, root)) {
        return false;
      }
      return insert_(tree, root, point, key);
    }
    return true;
  } else if (node_ispointer(root)) {
    node_t* quadrant = get_quadrant_(root, point);
    return quadrant == NULL ? 0 : insert_(tree, quadrant, point, key);
  }
  return false;
}


/*
** Public functions
*/

/**
 * Create new tree and return pointer
 *
 * quadtree_new(double min_x, min_y, max_x, max_y)
 * @return *tree
 */
quadtree_t *
quadtree_new(double minx, double miny, double maxx, double maxy) {
  quadtree_t *tree;
  if(!(tree = malloc(sizeof(*tree))))
    return NULL;
  tree->root = node_with_bounds(minx, miny, maxx, maxy);
  if(!(tree->root))
    return NULL;
  tree->key_free = NULL;
  tree->length = 0;
  return tree;
}

/**
 * Insert point to the tree
 *
 * quadtree_insert(quadtree_t *tree, double x, y, void *key)
 * @return bool
 */
bool
quadtree_insert(quadtree_t *tree, double x, double y, void *key) {
  point_t *point;
  if(!(point = point_new(x, y))) return false;
  if(!node_contains_(tree->root, point)) return false;
  if(!insert_(tree, tree->root, point, key)) return false;
  tree->length++;
  return true;
}

/**
 * Search if tree has point
 *
 * quadtree_search(quadtree_t *tree, double x, y)
 * @return *point
 */
point_t *
quadtree_search(quadtree_t *tree, double x, double y) {
  return find_(tree->root, x, y);
}

/**
 * Destroy tree
 *
 * quadtree_free(quadtree_t *tree)
 * @return void
 */
void
quadtree_free(quadtree_t *tree) {
  if(tree->key_free != NULL) {
    node_free(tree->root, tree->key_free);
  } else {
    node_free(tree->root, elision_);
  }
  free(tree);
}

/**
 * Walks in tree, works like each for points
 *
 *                             void ascent        void descent
 * quadtree_walk(node_t *root, fun(node_t *node), fun(node_t *node))
 * @return void
 */
void
quadtree_walk(node_t *root, void (*descent)(node_t *node),
                            void (*ascent)(node_t *node)) {
  (*descent)(root);
  if(root->nw != NULL) quadtree_walk(root->nw, descent, ascent);
  if(root->ne != NULL) quadtree_walk(root->ne, descent, ascent);
  if(root->sw != NULL) quadtree_walk(root->sw, descent, ascent);
  if(root->se != NULL) quadtree_walk(root->se, descent, ascent);
  (*ascent)(root);
}

/**
 * Find points in bbox
 *
 * quadtree_within(quadtree_t *tree, bbox_t *bbox, results_t *results)
 * @return void
 */
void
quadtree_within(node_t *root, bounds_t *bounds, within_callback_t cb) {
  if (node_isleaf(root)) {
    cb(root->point);
  } else {
    if (root->sw && bounds_intersect(bounds, root->sw)) {
      quadtree_within(root->sw, bounds, cb);
    }
    if (root->se && bounds_intersect(bounds, root->se)) {
      quadtree_within(root->se, bounds, cb);
    }
    if (root->nw && bounds_intersect(bounds, root->nw)) {
      quadtree_within(root->nw, bounds, cb);
    }
    if (root->ne && bounds_intersect(bounds, root->ne)) {
      quadtree_within(root->ne, bounds, cb);
    }
  }
}
