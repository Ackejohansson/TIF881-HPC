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
  

  int max_nr_cells = 10;
  if (nr_cells < max_nr_cells)
    max_nr_cells = nr_cells;
  int nr_blocks = nr_cells / max_nr_cells + 1; // COulb be error here

  //short* cell_block = (short*)aligned_alloc(64, sizeof(short*) * max_nr_cells * 3);
  //short** matrix_block = (short**)aligned_alloc(64, sizeof(short*) * max_nr_cells);
  short* cell_block = (short*)malloc(sizeof(short*) * max_nr_cells * 3);
  short** matrix_block = (short**)malloc(sizeof(short*) * max_nr_cells);
  short base_cell[3] = {0, 0, 0};

  for (size_t i = 0; i < max_nr_cells; i++)
    matrix_block[i] = cell_block + i * 3;
  
  short base_cell[3] = {0, 0, 0};
  for(int i=0; i<max_nr_cells; i++){
    char cell[cell_byte+1];
    fseek(file, i*cell_byte, SEEK_SET);
    fgets(cell, cell_byte+1, file);
    base_cell = parse(cell);
    for (int j=0; j<nr_blocks; j++){
      for (int k=0; k<max_nr_cells; k++){
        fgets(cell, cell_byte+1, file);
        matrix[i][j] = parse(cell);
      }
      compute_distance(base_cell, matrix[i][j]);
    }
    
    }

  // Print all numbers in matrix 
  printf("Printing matrix...\n");
  for (int i=0; i<max_nr_cells; ++i){
    for (int j=0; j<3; ++j){
      printf("%hd ", matrix_block[i][j]);
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

      printf("%hd\n", (short)atoi(num));
      matrix_block[i][j] = (short)atoi(num); // TODO: Find a better way of doing this
}