#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <unistd.h>
#include <string.h>

#define TOT_DIST 3465


///////////////////////////////////////////////////////////////////////////////////////////
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
  const size_t cell_byte = 24; //sizeof("+00.000 -00.000 +00.000");
  size_t nr_cells = file_size / cell_byte;
  printf("Number of cells: %zu\n", nr_cells);
  
  // Allocate memory
  int cells_read_max = 10;
  if (nr_cells < cells_read_max)
    cells_read_max = nr_cells;
  int nr_blocks = ceil(nr_cells / cells_read_max);
  int matrix_block[cells_read_max][3];
  int base_cell[3] = {0, 0, 0};


  for(int i=0; i<cells_read_max; i++){
    char cell[cell_byte+1];
    fscanf(file, "%d %d %d", &base_cell[0], &base_cell[1], &base_cell[2]);
    for (int j=0; j<nr_blocks; j++){
      for (int k=0; k<cells_read_max; k++){
        fscanf(file, "%hd %hd %hd", &matrix_block[k][0], &matrix_block[k][1], &matrix_block[k][2])
      }
      for (int k=0; k<cells_read_max; k++){
        int sq_xdiff = (matrix_block[k][0]-base_cell[0])*(matrix_block[k][0]-base_cell[0]);
        int sq_ydiff = (matrix_block[k][1]-base_cell[1])*(matrix_block[k][1]-base_cell[1]);
        int sq_zdiff = (matrix_block[k][2]-base_cell[2])*(matrix_block[k][2]-base_cell[2]);
        int dist = (int)sqrtf(sq_xdiff + sq_ydiff + sq_zdiff)*100.0f + 0.5f;
      }
    }
  }

  // Print all numbers in matrix 
  printf("Printing matrix...\n");
  for (int i=0; i<cells_read_max; ++i){
    for (int j=0; j<3; ++j){
      printf("%d ", matrix_block[i][j]);
    }
    printf("\n");
  }

  return 0;
}



void parse(){
      for (int j=0; j<3; ++j){
      char num[7];
      num[0] = cell[8*j + 0];
      num[1] = cell[8*j + 1];
      num[2] = cell[8*j + 2];

      num[3] = cell[8*j + 4];
      num[4] = cell[8*j + 5];
      num[5] = cell[8*j + 6];
      num[6] = '\0';
      printf("Cell first: %s\n", num[0]);
      printf("Cell second: %s\n", num[1]);

      printf("%hd\n", (int)atoi(num));
      matrix_block[i][j] = (int)atoi(num); // TODO: Find a better way of doing this
}