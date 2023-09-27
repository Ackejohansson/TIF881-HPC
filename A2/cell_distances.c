#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <unistd.h>

#define SIZE 10

// Function prototypes
int setMPThreadNumber(int argc, char *argv[], int *MP_threads);
void read_data(double *x, double *y, double *z);
void compute_distances(double *distances, double *x, double *y, double *z);

///////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
  // Set the number of threads
  int MP_threads = -1;
  setMPThreadNumber(argc, argv, &MP_threads);
  printf("Number of threads sat to : %d\n", MP_threads);
  

  // Read the data to memory
  printf("Reading data...\n");
  double x[SIZE], y[SIZE], z[SIZE];
  read_data(x, y, z);
  printf("\nData read.\n");


  // Compute the distances
  printf("Computing distances...\n");
  int total_distances = SIZE*(SIZE-1)/2;
  double distances[total_distances];
  for (int i = 0; i < total_distances; i++)
    distances[i] = -1.0;
  
  compute_distances(distances, x, y, z);

  for (int i = 0; i < total_distances; i++)
    printf("%lf ", distances[i]);
  printf("\nDistances computed.\n");
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////

int setMPThreadNumber(int argc, char *argv[], int *MP_threads) {
  int option;
  while ((option = getopt(argc, argv, "t:")) != -1)
    if (option == 't') 
      *MP_threads = atoi(optarg);

  if (*MP_threads == -1) {
    fprintf(stderr, "You must provide a value for number of threads ex: -t4\n");
    exit(EXIT_FAILURE);
  }
  omp_set_num_threads(MP_threads);
  return 0;
}

void read_data(double *x, double *y, double *z) {
  FILE *file = fopen("./cells", "r");

  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  while (fscanf(file, "%lf %lf %lf", &x[i], &y[i], &z[i]) == 3) {
    if (i >= SIZE) {
      printf("Warning: More than max data points found. Array size exceeded.\n");
      break;
    }
    i++;
  }

  if (ferror(file)) {
    perror("Error reading data from file");
    fclose(file);
    exit(EXIT_FAILURE);
  }
  fclose(file);

  if (i == 0) {
    printf("No data found in the file.\n");
    exit(EXIT_SUCCESS); // Exit successfully without an error
  }

  printf("Printing the data:\n");
  printf("x: ");
  for (int j = 0; j < i; j++) {
    printf("%f ", x[j]);
  }
  printf("\ny: ");
  for (int j = 0; j < i; j++) {
    printf("%f ", y[j]);
  }
  printf("\nz: ");
  for (int j = 0; j < i; j++) {
    printf("%f ", z[j]);
  }
}

void compute_distances(double *distances, double *x, double *y, double *z) {
  int index = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = i + 1; j < SIZE; j++) {
      distances[index] = sqrt(pow(x[j]-x[i],2)+pow(y[j]-y[i],2)+pow(z[j]-z[i],2));
      index++;
    }
  }
}
