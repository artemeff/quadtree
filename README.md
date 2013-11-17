### quadtree

---

### Benchmarks

```
[ok] 0.1114s of 0.120000s
     fill_small_tree

[ok] 0.0097s of 0.010000s
     walking_in_small_tree

[ok] 0.0103s of 0.015000s
     finds_0_0_200_200_in_small_tree_walk
     
[ok] 0.0032s of 0.004000s
     finds_0_0_200_200_in_small_tree_within
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
