#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <unistd.h>

#define NR_READ 3
#define TOT_DIST 3465

// Function prototypes
int setMPThreadNumber(int argc, char *argv[], int *MP_threads);

///////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
  // Set the number of threads
  int MP_threads = 1;
  setMPThreadNumber(argc, argv, &MP_threads);
  printf("Number of threads sat to : %d\n", MP_threads);
  

  // Read the data to memory
  printf("Reading data...\n");
  FILE *file = fopen("./cells", "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  const size_t cell_byte = sizeof("+00.000 -00.000 +00.000");
  size_t nr_cells = file_size / cell_byte;
  
  double x1, y1, z1, x2, y2, z2;
  char *block = malloc(cell_byte * nr_cells);
  char *cell_ptr = block;
  printf("Cell byte size: %zu\n", cell_byte);
  printf("Number of cells: %zu\n", nr_cells);

  
  int output[TOT_DIST] = {0};
  int index = 0;
  for (int i = 0; i < nr_cells-1; ++i){
    size_t nr_read = fread(block, cell_byte, 1, file);
    sscanf(block, "%lf %lf %lf", &x1, &y1, &z1);
    
    for (int j = i+1; j < nr_cells; j += NR_READ){
      size_t nr_cells_read = fread(block, cell_byte, NR_READ, file);
      cell_ptr = block;

        for (int k = 0; k < nr_cells_read; k++){
          sscanf(cell_ptr, "%lf %lf %lf", &x2, &y2, &z2);
          
          double distance = (sqrt(pow(x2-x1,2)+pow(y2-y1,2)+pow(z2-z1,2))*100);
          int dist = (int)round(distance);
          printf("Distance: %d\n", dist);
          printf("(%lf %lf %lf) (%lf %lf %lf)\n", x1, y1, z1, x2, y2, z2);
          output[dist] += 1;
          cell_ptr += cell_byte;
          index++;
        }
    }
    // DIFFERENT LOCALLY AND ON GANTENB. Exclude i+1 in ganten.
    fseek(file, (i + 1) * cell_byte+i+1, SEEK_SET);
  }
  printf("Index: %d\n", index);
  printf("x1: %lf, y1: %lf, z1: %lf\n", x1, y1, z1);
  printf("x2: %lf, y2: %lf, z2: %lf\n", x2, y2, z2);
  fclose(file);
  free(block);
  printf("Data read.\n");

  // Print output
  printf("Printing output...\n");
  for (int i = 0; i < TOT_DIST; ++i){
    if (output[i] != 0){
      printf("%.2f %i\n", i / 100.0, output[i]);
    }
  }

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
  //omp_set_num_threads(MP_threads);
  return 0;
}