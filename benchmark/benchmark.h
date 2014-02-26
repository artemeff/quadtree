#ifndef __BENCHMARK_H__
#define __BENCHMARK_H__

#include <stdio.h>
#include <time.h>

#define bench(fn) b_measure(#fn, fn);
#define start() start_time = clock();
#define stop() duration = (float) (clock() - start_time) / CLOCKS_PER_SEC;

static int fail;
static clock_t start_time;
static float duration;

void b_desc() {
  printf("\n\x1b[34m\tbenchmarks\x1b[0m\n\n");
}

void b_measure(const char *descr, void (*bm)()) {
  bm();

  printf("%.4fs \x1b[0m%s\x1b[0m\n", duration, descr);
}

int b_isok() {
  return fail;
}

#endif
