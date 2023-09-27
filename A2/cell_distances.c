#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <unistd.h>

#define SIZE 9

// Function prototypes
int setMPThreadNumber(int argc, char *argv[], int *MP_threads);
void read_data();
void read_binary_data();

///////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
  // Set the number of threads
  int MP_threads = -1;
  setMPThreadNumber(argc, argv, &MP_threads);
  //omp_set_num_threads(MP_threads);
  printf("Number of threads sat to : %d\n", MP_threads);
  
  // Read the data to memory
  double x[SIZE], y[SIZE], z[SIZE];
  printf("Reading data...\n");
  //read_binary_data();
  read_data(x, y, z);
  printf("\nData read.\n");

  // Compute the distances
  printf("Computing distances...\n");
  double distances[SIZE*SIZE/2];
  compute_distances(distances, x, y, z);



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
    i++;
    if (i >= SIZE) {
      printf("Warning: More than %d data points found. Array size exceeded.\n", SIZE);
      break;
    }
  }

  if (ferror(file)) {
    perror("Error reading data from file");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  fclose(file);

  // Check if any data was read
  if (i == 0) {
    printf("No data found in the file.\n");
    exit(EXIT_SUCCESS); // Exit successfully without an error
  }

  printf("Printing the data:\n");
  // Process the data as needed
  for (int j = 0; j < i; j++) {
    printf("%f ", x[j]);
  }
}

void compute_distances(double *distances, double *x, double *y, double *z){
  int index = 0;
  for (int i = 0; i < SIZE; i++)
    for (int j = i+1; j < SIZE; j++) {
      distances[index] = sqrt(pow(x[i]-x[j],2) + pow(y[i]-y[j],2) + pow(z[i]-z[j],2));
      index++;
    }
}