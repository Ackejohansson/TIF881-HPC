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
#include <string.h>

static inline double complex fofx(double complex x, int d){
  return cpow(x, d) - 1.0;
}

static inline double complex fprimeofx(double complex x, int d){
  return d * cpow(x, d - 1);
}

static inline void parse_args(int argc, char *argv[], int *num_threads, int *size, int *d){
  char *ptr;
  if (argc == 4) {
    for (int i = 1; i < argc - 1; i++) {
      ptr = strchr(argv[i], 't');
      if (ptr)
        *num_threads = strtol(++ptr, NULL, 10);
      else {
        ptr = strchr(argv[i], 'l');
        *size = strtol(++ptr, NULL, 10);
      }
    }
    *d = strtol(argv[argc - 1], NULL, 10);
  } else {
    printf("Not enough arguments\n");
    printf("Usage: newton -t<numberOfThreads> -l<numberOfLines> <degreeOfPolynomial>\n");
    exit(EXIT_FAILURE);
  }
  printf("Number of threads: %d\n", *num_threads);
  printf("Size of grid: %d\n", *size);
  printf("Degree of polynomial: %d\n", *d);
}

void allocateMemory(int size, double complex ***matrix_attractor, int ***matrix_convergence) {
  double complex *attractor_data = (double complex *)malloc(size * size * sizeof(double complex));
  int *convergence_data = (int *)malloc(size * size * sizeof(int));
  if (attractor_data == NULL || convergence_data == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }
  
  *matrix_attractor = (double complex **)malloc(size * sizeof(double complex *));
  *matrix_convergence = (int **)malloc(size * sizeof(int *));
  if (*matrix_attractor == NULL || *matrix_convergence == NULL) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < size; i++) {
    (*matrix_attractor)[i] = &attractor_data[i * size];
    (*matrix_convergence)[i] = &convergence_data[i * size];
  }
}

static inline void compute_distances(int size, int d, double complex **matrix_attractor, int **matrix_convergence){
  double tol = 1e-6;
  int max_iter = 128;
  double complex x_new, x_old;
  for (int i = 0; i < size; i++){
    double a = (double)i/size-2.0;
    for (int j = 0; j < size; j++){
      int iter = 0;
      x_old = a - ((double)j/size+2.0)*I;
      for(int iter=0; iter < max_iter; iter++){
        x_new = x_old - fofx(x_old, d)/fprimeofx(x_old, d);
        
        if (cabs(fofx(x_new, d)) < 1e-3) {
          break;
        }
        if (cabs(creal(x_new)) > 1e10 || cabs(cimag(x_new)) > 1e10) {
          break;
        }
        x_old = x_new;
      }
      matrix_attractor[i][j] = x_new;
      matrix_convergence[i][j] = iter;
    }
  }
}

int main(int argc, char *argv[]){
  // Parse arguments
  int num_threads = 1;
  int size = 10;
  int d = 2;
  //parse_args(argc, argv, &num_threads, &size, &d);

  // Allocate memory
  double complex **matrix_attractor;
  int **matrix_convergence;
  allocateMemory(size, &matrix_attractor, &matrix_convergence);

  // Compute the distances 
  compute_distances(size, d, matrix_attractor, matrix_convergence);

  
  // Print result 
  printf("Result:\n");
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      printf("%f + %fi \n", creal(matrix_attractor[i][j]), cimag(matrix_attractor[i][j]));
    }
  }
  free(*matrix_attractor);
  free(*matrix_convergence);
  free(matrix_attractor);
  free(matrix_convergence);
  return 0;
}
