#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static inline void initLinearIndex(size_t* p, size_t size) {
  for (size_t ix = 0; ix < size; ++ix)
    p[ix] = ix;
}

static inline void initJumpIndex(size_t* p, size_t size) {
  size_t size_jump = 1000;
  for (size_t jx = 0, kx = 0; jx < size_jump; ++jx)
    for (size_t ix = jx; ix < size; ix += size_jump, ++kx)
      p[ix] = kx;
}

static inline double benchmarkOperation(size_t* p, double* y, const double* x, double a, size_t size, void (*initFunc)(size_t*, size_t)) {
  initFunc(p, size);
  clock_t start_time = clock();
  for (int i = 0; i < 1000; i++) {
    for (size_t kx = 0; kx < size; ++kx) {
      size_t jx = p[kx];
      y[jx] += a * x[jx];
    }
  }
  clock_t end_time = clock();
  int random_index = rand() % size;
  printf("Random element of y at index %d: %lf\n", random_index, y[random_index]);
  return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

int main() {
  size_t size = 1000000;
  double* x = (double*)malloc(size * sizeof(double));
  double* y = (double*)malloc(size * sizeof(double));
  size_t* p = (size_t*)malloc(size * sizeof(size_t));
  double a = 0.5;

  if (x == NULL || y == NULL || p == NULL) {
    printf("Error allocating memory\n");
    return 1;
  }
  for (size_t ix = 0; ix < size; ++ix) {
    x[ix] = (double)rand() / RAND_MAX;
    y[ix] = (double)rand() / RAND_MAX;
  }

  // Benchmark linear init and update
  double linearTime = benchmarkOperation(p, y, x, a, size, initLinearIndex);
  printf("Time for linear init and update: %lf seconds\n", linearTime);

  // Benchmark jump init and update
  double jumpTime = benchmarkOperation(p, y, x, a, size, initJumpIndex);
  printf("Time for jump init and update: %lf seconds\n", jumpTime);

  initLinearIndex(p, size);
  clock_t start_time = clock();
  for (int i = 0; i < 1000; i++) {
    for ( size_t kx = 0; kx < size; ++kx )
      y[kx] += a * x[kx];
    }
  clock_t end_time = clock();
  printf("Time for direct address: %lf seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);
  int random_index = rand() % size;
  printf("Random element of y at index %d: %lf\n", random_index, y[random_index]);
  



  free(x);
  free(y);
  free(p);
  return 0;
}
