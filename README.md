### quadtree

---

### Benchmarks

```
[ok] 0.1095 of 0.120000
     insert_100000_times

[ok] 0.0096 of 0.010000
     walking_in_tree_with_100000_points
```

---

### Installation

```bash
$ git clone && cd
$ make test
$ make install
```

---

### Usage

Hello world:

```c
#include <stdio.h>
#include <quadtree.h>

int main() {
  int val = 10;
  quadtree_t *tree = quadtree_new(0, 0, 10, 10);
  quadtree_insert(tree, 1, 1, &val);
  quadtree_insert(tree, 2, 2, &val);
  quadtree_insert(tree, 3, 3, &val);

  printf("tree length: %d\n", tree->length);

  return 0;
}
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
