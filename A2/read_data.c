#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NR_CELLS 10

int main(){
  // open file
  FILE *file = fopen("./cells", "r");
   
  if(file == NULL){
    printf("Error: file pointer is null.");
    exit(1);
  }

  // allocate block of memory for the read
  const size_t cell_byte = sizeof("+00.000 -00.000 +00.000");
  printf("Cell byte size: %zu\n", cell_byte);
  char *block = malloc(cell_byte * NR_CELLS);
  char *cell_ptr = block;

  // read the file into the block
  size_t nr_read = fread(block, cell_byte, NR_CELLS, file);
  fclose(file);

  // Declare x1, y1, z1 as arrays
  double x1, y1, z1;
  double x2, y2, z2;

  // sscanf cells from block
  for(int i = 0; i < 1; i++){
    cell_ptr = block;
    sscanf(block, "%lf %lf %lf", &x1, &y1, &z1);
    for (int j = i+1; j < NR_CELLS; j++){
      cell_ptr += cell_byte;
      sscanf(cell_ptr, "%lf %lf %lf", &x2, &y2, &z2);
      
      double distance = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2) + pow(z1-z2, 2))*100;
      printf("Distance between cell %d and %d: %lf\n", i, j, distance);
    }
  }
  printf("x1: %lf, y1: %lf, z1: %lf\n", x1, y1, z1);
  printf("x2: %lf, y2: %lf, z2: %lf\n", x2, y2, z2);

  free(block);
  
  return 0;
}
