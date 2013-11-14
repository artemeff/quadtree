#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <stdio.h>
#include <time.h>

#define bench(fn, expect) b_measure(#fn, expect, fn);
#define start() start_time = clock();
#define stop() duration = (float) (clock() - start_time) / CLOCKS_PER_SEC;

static int fail;
static clock_t start_time;
static float duration;

void b_measure(const char *descr, double expect, void (*bm)()) {
  bm();

  if (expect > duration) {
    printf("\x1b[1;32m   [ok]\x1b[0m");
  } else {
    printf("\x1b[1;31m [fail]\x1b[0m");
    fail = 1;
  }

  printf("\t%.4f of %f\n", duration, expect);
  printf("\x1b[30m\t%s\x1b[0m\n", descr);
}

int b_isok() {
  return fail;
}

#endif
