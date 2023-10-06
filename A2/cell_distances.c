#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <unistd.h>
#include <string.h>

#define TOT_DIST 3465

int main(int argc, char *argv[]) {
  // Set the number of threads
  int nr_threads = 1;
  char* ptr = strchr(argv[1], 't');
  if (ptr) {
    nr_threads = strtol(++ptr, NULL, 10);
  }
  //omp_set_num_threads(nr_threads);
  printf("Number of threads sat to : %d\n", nr_threads);
  
  // Open file
  printf("Reading data...\n");
  FILE *file = fopen("./cells", "r");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  const size_t cell_byte = 24;
  size_t nr_cells = file_size / cell_byte;
  printf("Number of cells: %zu\n", nr_cells);
  
  // Allocate memory
  printf("Allocating memory...");
  int cells_read_max = 10;
  if (nr_cells < cells_read_max)
    cells_read_max = nr_cells;
  int nr_blocks = ceil((double)nr_cells / cells_read_max);
  double matrix_block[cells_read_max][3];
  for (int i=0; i<cells_read_max; i++){
    matrix_block[i][0] = 0.0;
    matrix_block[i][1] = 0.0;
    matrix_block[i][2] = 0.0;
  }
  double xBase, yBase, zBase;
  double xDummy, yDummy, zDummy;
  int distances[TOT_DIST]={0};
  printf("Number of blocks: %d\n", nr_blocks);
  int counter=0;
  // Read data from file
  printf("Reading data...\n");
  for(int i=0; i<cells_read_max; i++){
    fseek(file, i*cell_byte +i+1, SEEK_SET);
    fscanf(file, "%lf %lf %lf", &xBase, &yBase, &zBase);
    for (int j = i+1; j < nr_cells; j += cells_read_max){
      int index = 0;
      while(index < cells_read_max && fscanf(file, "%lf %lf %lf", &xDummy, &yDummy, &zDummy) != EOF){
        matrix_block[index][0] = xDummy;
        matrix_block[index][1] = yDummy;
        matrix_block[index][2] = zDummy;
        ++index;
      }
      // Calculate distances
      //printf("Calculating distances...\n");
      for (int k=0; k<index; k++){ // cant start on 0?
        double sq_xdiff = (matrix_block[k][0]-xBase)*(matrix_block[k][0]-xBase);
        double sq_ydiff = (matrix_block[k][1]-yBase)*(matrix_block[k][1]-yBase);
        double sq_zdiff = (matrix_block[k][2]-zBase)*(matrix_block[k][2]-zBase);
        double distance = sqrt(sq_xdiff + sq_ydiff + sq_zdiff)*100;
        //printf("Distance: %f\n", distance);
        int dist = (int)round(distance);
        //printf("Distance: %d\n", dist);
        //printf("Difference done...\n");
        ++distances[dist];
        ++counter;
      }
    }
  }
  fclose(file);
  printf("Printing results...\n");
  // Print value of distances
  
  for (int i=0; i<TOT_DIST; i++)
    if(distances[i] != 0)
      printf("%d %d\n", i, distances[i]);
  printf("Counter: %d\n", counter);
  return 0;
}