#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <stdio.h>
#include <time.h>

#define bench(fn, expect) b_measure(#fn, expect, fn);
#define start() startTime = clock();
#define stop() duration = (float) (clock() - startTime) / CLOCKS_PER_SEC;

static int fail;
static clock_t startTime;
static float duration;

void b_measure(const char *descr, double expect, void (*bm)()) {
  bm();

  if (expect > duration) {
    printf("\x1b[1;32m   [ok]\x1b[0m\t");
  } else {
    printf("\x1b[1;31m [fail]\x1b[0m\t");
    fail = 1;
  }

  printf("%.4f of %f\n", duration, expect);
  printf("\x1b[30m\t%s\x1b[0m\n", descr);
}

int b_isok() {
  return fail;
}

#endif
