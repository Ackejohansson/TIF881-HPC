#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void row_sums(double *sums, const double **matrix, size_t nrs, size_t ncs){
  for (size_t ix = 0; ix < nrs; ++ix) {
    double sum = 0.;
    for (size_t jx = 0; jx < ncs; ++jx)
      sum += matrix[ix][jx];
    sums[ix] = sum;
  }
}

void row_sums_unrolled2(double *sums, const double **matrix, size_t nrs, size_t ncs){
  for (size_t ix = 0; ix < nrs; ++ix) {
    double sum0 = 0.;
    double sum1 = 0.;
    for (size_t jx = 0; jx < ncs; jx += 2) {
      sum0 += matrix[ix][jx];
      sum1 += matrix[ix][jx + 1];
    }
    sums[ix] = sum0 + sum1;
  }
}

int main(){
  double *asentries = (double*) malloc(SIZE*SIZE*sizeof(double));
  double **matrix = (double**) malloc(SIZE*sizeof(double*));
  
  if (matrix == NULL || asentries == NULL){
    printf("Error allocating memory\n");
    return 1;
  }

  for (int ix = 0; ix < SIZE; ++ix)
    matrix[ix] = asentries + SIZE*ix;

  // Initialize the matrix with random numbers
  srand(time(NULL));
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      matrix[i][j] = (double)rand() / RAND_MAX;
    }
  }

  double rowsums[SIZE];
  clock_t start, end;
  double cpu_time_used;

  // Benchmark row_sums
  start = clock();
  for (int i = 0; i < 5000; i++)
    row_sums(rowsums, (const double **)matrix, SIZE, SIZE);

  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Time for row_sums: %lf seconds\n", cpu_time_used);
  
  int random_index = rand() % SIZE;
  printf("Random element from row_sums: %lf\n", rowsums[random_index]);

  for (int i = 0; i < SIZE; ++i)
    rowsums[i] = 0.0;


  // Benchmark row_sums_unrolled2
  start = clock();
  for (int i = 0; i < 5000; i++)
    row_sums_unrolled2(rowsums, (const double **)matrix, SIZE, SIZE);

  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Time for row_sums_unrolled2: %lf seconds\n", cpu_time_used);
  
  random_index = rand() % SIZE;
  printf("Random element from row_sums_unrolled2: %lf\n", rowsums[random_index]);

  free(matrix);
  free(asentries);
  return 0;
}
