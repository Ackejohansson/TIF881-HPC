#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TOT_DIST 3465

int main(int argc, char *argv[]) {
  // Variables
  int cells_read = 10;

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

  // Get number of cells
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  const size_t cell_byte = 24;
  size_t nr_cells = file_size / cell_byte;
  printf("Number of cells: %zu\n", nr_cells);

  // Allocate memory
  printf("Allocating memory...");
  if (nr_cells < cells_read) // WILL BE PUT ON THE HEAP?!
    cells_read = nr_cells;
  int nr_blocks = (nr_cells+cells_read-1) / cells_read;
  short cell_matrix[cells_read][3];
  for (int i=0; i<cells_read; i++){
    cell_matrix[i][0] = 0;
    cell_matrix[i][1] = 0;
    cell_matrix[i][2] = 0;
  }
  short xBase, yBase, zBase;
  short xDummy, yDummy, zDummy;
  int distances[TOT_DIST]={0};
  printf("Number of blocks: %hd\n", nr_blocks);
  

  // Read data from file
  printf("Reading data...\n");
  for(int i=0; i<nr_cells-1; i++){
    fseek(file, i*cell_byte +i+1, SEEK_SET);
    fscanf(file, "%hd %hd %hd", &xBase, &yBase, &zBase);
    for (int j = i+1; j < nr_cells; j += cells_read){
      int index = 0;
      while(index < cells_read && fscanf(file, "%hd %hd %hd", &xDummy, &yDummy, &zDummy) != EOF){
        cell_matrix[index][0] = xDummy;
        cell_matrix[index][1] = yDummy;
        cell_matrix[index][2] = zDummy;
        ++index;
      }
      // Calculate distances
      //printf("Calculating distances...\n");
      for (int k = 0; k < index; k++) {
        int sq_xdiff = (cell_matrix[k][0] - xBase) * (cell_matrix[k][0] - xBase);
        int sq_ydiff = (cell_matrix[k][1] - yBase) * (cell_matrix[k][1] - yBase);
        int sq_zdiff = (cell_matrix[k][2] - zBase) * (cell_matrix[k][2] - zBase);
        int sq_diff = sq_xdiff + sq_ydiff + sq_zdiff;
        int dist = (int)(sqrtf( (float)(sq_diff)) / 10.0f+0.5f);
        // printf("Distance: %d\n", dist);
        distances[dist]++;
      }
    }
  }
  fclose(file);
  printf("Printing results...\n");
  // Print value of distances
  
  for (int i=0; i<TOT_DIST; i++)
    if(distances[i] != 0)
      printf("%d %d\n", i, distances[i]);
  return 0;
} 