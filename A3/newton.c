/*
  Parse the command line
  Synchronize the threads
  Data transfer between threads
  Check convergence of the solution
  Computation of next iteration
  Write to file
*/
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

static inline double fofx(double complex x, int d){
  return cpow(x, d) - 1.0;
}

static inline double complex fprimeofx(double complex x, int d){
  return d*cpow(x, d-1);
}

static inline parse_args(int argc, char *argv[]){
  
}

int main(int argc, char *argv[]){
  parse_args(argc, *argv);
  
  int size = 1000;
  double complex complex_grid[size][size];
  int d = 7;
  double complex x_new, x_old;
  double tol = 1e-6;
  int max_iter = 128;

  double complex matrix_attractor = (double complex *)malloc(size*size*sizeof(double complex));
  double complex matrix_convergence = (double complex *)malloc(size*size*sizeof(double complex));
  
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      int iter = 0;
      for(int iter=0; iter < max_iter; iter++){
        x_new = x_old - fofx(x_old, d)/fprimeofx(x_old, d);
        
        if (cabs(fofx(x_new, d)) < 1e-3 || cabs(x_new) < 1e-3) {
          break;
        }
        if (cabs(creal(x_new)) > 1e10 || cabs(cimag(x_new)) > 1e10) {
          break;
        }
        memcpy(x_old, x_new, sizeof(double complex));
      }
      complex_grid[i][j] = x_new;
    }
  }
  

  return 0;
}
