#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ROWS 1000
#define COLS 1000

void row_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs) {
  for (size_t ix = 0; ix < nrs; ++ix) {
    double sum = 0.;
    for (size_t jx = 0; jx < ncs; ++jx)
      sum += matrix[ix][jx];
    sums[ix] = sum;
  }
}

void col_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs) {
  for (size_t jx = 0; jx < ncs; ++jx) {
    double sum = 0.;
    for (size_t ix = 0; ix < nrs; ++ix)
      sum += matrix[ix][jx];
    sums[jx] = sum;
  }
}

void col_sums_improved(double * sums, const double ** matrix, size_t nrs, size_t ncs) {
  for (size_t ix = 0; ix < ncs; ++ix)
    for (size_t jx = 0; jx < nrs; ++jx)
      sums[jx] += matrix[ix][jx];
}

int main() {
    double * asentries = (double *)malloc(ROWS * COLS * sizeof(double *));
    double ** matrix = (double **)malloc(ROWS * sizeof(double *));
    for (int ix = 0; ix < ROWS; ++ix)
        matrix[ix] = asentries + COLS * ix;

    if (matrix == NULL || asentries == NULL) {
        printf("Error allocating memory\n");
        return 1;
    }

    for (size_t i = 0; i < ROWS; ++i)
        for (size_t j = 0; j < COLS; ++j)
            matrix[i][j] = (double)rand() / RAND_MAX;

    double rowsums[ROWS];
    double colsums[COLS];
    double improved_colsums[COLS];  // Add an array for improved_colsums

    // Benchmark row_sums
    clock_t start = clock();
    for (int i = 0; i < 10000; ++i)
        row_sums(rowsums, (const double **)matrix, ROWS, COLS);
    clock_t end = clock();
    printf("row_sums took %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Benchmark col_sums
    start = clock();
    for (int i = 0; i < 10000; ++i)
        col_sums(colsums, (const double **)matrix, ROWS, COLS);
    end = clock();
    printf("col_sums took %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Benchmark col_sums_improved
    start = clock();
    for (int i = 0; i < 10000; ++i)
        col_sums_improved(improved_colsums, (const double **)matrix, ROWS, COLS);
    end = clock();
    printf("col_sums_improved took %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("rowsums[0] = %f\n", rowsums[0]);
    printf("colsums[0] = %f\n", colsums[0]);
    printf("improved_colsums[0] = %f\n", improved_colsums[0]);

    free(matrix);
    free(asentries);
    return 0;
}
