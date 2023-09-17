#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

int main(){
    double matrix[ROWS][COLS];

    // COmpute the row sums and colum sums of the matrix
    for (size_t i = 0; i<ROWS; ++i){
        for (size_t j = 0; j<COLS; ++j){
            matrix[i][j] = (double)rand()/RAND_MAX;
        }
    }

    double rowsums[ROWS];
    double colsums[COLS];
    clock_t start_time, end_time;


    // Run rows
    start_time = clock();
    row_sums(rowsums, (const double **)matrix, ROWS, COLS);
    end_time = clock();
    printf("Time for row_sums: %lf\n", (double)(end_time - start_time)/CLOCKS_PER_SEC);

    // Run cols
    start_time = clock();
    col_sums(colsums, (const double **)matrix, ROWS, COLS);
    end_time = clock();
    printf("Time for col_sums: %lf\n", (double)(end_time - start_time)/CLOCKS_PER_SEC);

    printf("Random element of rowSums: %lf\n", rowsums[500]);
    printf("Random element of rowCols: %lf\n", colsums[500]);

    return 0;
}