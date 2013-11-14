#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>

#define case(fn)     t_desc(#fn, fn);
#define assert(expr) t_assert(expr, #expr, __LINE__, __FILE__);
#define pending(msg) t_assert(-1, msg, __LINE__, __FILE__);

static int fail;

void t_desc(char *name, void (*func)()) {
  printf("\n\x1b[34m\t%s\x1b[0m\n\n", name);
  (*func)();
}

void t_assert(int r, const char *cond, int line, const char *file) {
  if (r == 1) {
    printf("\x1b[1;32m   [ok]\x1b[0m\t");
  } else if (r == 0) {
    printf("\x1b[1;31m [fail]\x1b[0m\t");
    fail = 1;
  } else {
    printf("\x1b[33m [pend]\x1b[0m\t");
  }

  printf("%s\n", cond);
  printf("\x1b[30m\t%s:%d\x1b[0m\n", file, line);
}

int t_isok() {
  return fail;
}

#endif
