#include <stdlib.h>
#include <stdio.h>

#define ROWS 1000
#define COLS 1000

void row_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs){
  for ( size_t ix = 0; ix < nrs; ++ix ) {
    double sum = 0.;
    for ( size_t jx = 0; jx < ncs; ++jx )
      sum += matrix[ix][jx];
    sums[ix] = sum;
  }
}

void col_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs){
  for ( size_t jx = 0; jx < ncs; ++jx ) {
    double sum = 0.;
    for ( size_t ix = 0; ix < nrs; ++ix )
      sum += matrix[ix][jx];
    sums[jx] = sum;
  }
}

void col_sums_improved(double * sums, const double ** matrix, size_t nrs, size_t ncs){
  for ( size_t ix = 0; jx < ncs; ++jx ) {
    double sum = 0.;
    for ( size_t jx = 0; ix < nrs; ++ix )
      sum[jx] += matrix[ix][jx];
  }
}

int main(){
  double *asentries = (double*) malloc(ROWS * COLS * sizeof(double*));
  double **matrix = (double**) malloc(ROWS * sizeof(double*));
  for ( int ix = 0; ix < ROWS; ++ix )
    matrix[ix] = asentries + COLS*ix;
  
  if (matrix == NULL || asentries == NULL){
    printf("Error allocating memory\n");
    return 1;
  }
  
  // Compute the row sums and colum sums of the matrix
  for (size_t i = 0; i<ROWS; ++i){
    for (size_t j = 0; j<COLS; ++j){
      matrix[i][j] = (double)rand()/RAND_MAX;
    }
  }

  double rowsums[ROWS];
  

  row_sums(rowsums, (const double **)matrix, ROWS, COLS);
  printf("Random element of rowSums: %lf\n", rowsums[500]);
/*
  double colsums[COLS];
  col_sums(colsums, (const double **)matrix, ROWS, COLS);
  printf("Random element of rowCols: %lf\n", colsums[500]);
  */
  free(matrix);
  free(asentries);
  return 0;
}