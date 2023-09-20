#include <stdio.h>
#include <stdlib.h>

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
  double *asentries = (double*) malloc(SIZE*SIZE*sizeof(double*));
  double **matrix = (double**) malloc(SIZE*sizeof(double*));
  for (int ix = 0; i < SIZE; ++i)
    matrix[ix] = asentries + SIZE*ix;
  
  if (matrix == NULL || asentries == NULL){
    printf("Error allocating memory\n");
    return 1;
  }
  double rowsums[SIZE];

  row_sums(rowsums, (const double **)matrix, SIZE, SIZE);
  printf("Random element: %lf\n", rowsums[500]);

  row_sums_unrolled2(rowsums, (const double **)matrix, SIZE, SIZE);
  printf("Random element: %lf\n", rowsums[500]);
  
  return 0;
}