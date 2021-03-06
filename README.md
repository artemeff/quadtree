### quadtree

---

### Installation

```bash
$ git clone && cd
$ make
$ make install
```

---

### Usage

```c
#include <stdio.h>
#include <quadtree.h>

int main() {
  int val = 10;
  quadtree_t *tree = quadtree_new(0, 0, 10, 10);
  quadtree_insert(tree, 1, 1, 1, &val);
  quadtree_insert(tree, 2, 2, 2, &val);
  quadtree_insert(tree, 3, 3, 3, &val);

  printf("tree length: %d\n", tree->length);

  return 0;
}
```

Finds in tree:

```c
result_node_t *head, *cur;

void within_callback(point_t *point) {
  printf("%d\n", point->x);
}

quadtree_within(tree->root, bbox, within_callback);
```

Walks in tree:

```c
void ascent(node_t *node) {
  if (node && node->point) {
    printf("%d\n", node->point->x);
  }
}

void descent(node_t *node) {
  if (node && node->point) {
    printf("%d\n", node->point->x);
  }
}

quadtree_walk(tree->root, &ascent, &descent);
```

Reference:

```c
// Create new tree and return pointer
quadtree_t *
quadtree_new(double minx, double miny, double maxx, double maxy)

// Insert point to the tree and return point pointer
point_t *
quadtree_insert(quadtree_t *tree, double x, double y, void *key, bool update)

// Search if tree has point and return point pointer
point_t *
quadtree_search(quadtree_t *tree, double x, double y)

// Destroy tree
void
quadtree_free(quadtree_t *tree)

// Walks in tree, works like each for points
void
quadtree_walk(node_t *root, void (*descent)(node_t *node),
                            void (*ascent)(node_t *node))

// Find points in bbox
void
quadtree_within(node_t *root, bounds_t *bounds, within_callback_t cb)
```

---

### Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Make changes
4. `make test benchmark`
5. Commit your changes (`git commit -am 'add some feature'`)
6. Push to the branch (`git push origin my-new-feature`)
7. Create new Pull Request
