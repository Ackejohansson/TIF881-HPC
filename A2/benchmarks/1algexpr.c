#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <omp.h>

#define NUM_DISTANCES 3465
#define CELL_SIZE 24
#define BLOCK_SIZE 2000

static inline short parse_coord(char* s) {
  short x;
  x =   10000 * (s[1] - '0')
      + 1000  * (s[2] - '0')
      + 100   * s[4] 
      + 10    * s[5] 
      +         s[6] 
      - 5328;

  if (s[0] == '-') {
    return -x;
  } else {
    return x;
  }
}


int main( int argc, char* argv[])
{
  int frequencies[NUM_DISTANCES]={0};

  FILE* file = fopen("cells", "r");
  if (file == NULL) {
    perror("Error opening file");
    return 1;
  }

  fseek(file, 0, SEEK_END);
  size_t file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  int num_blocks = (int) (file_size + BLOCK_SIZE * CELL_SIZE - 1)/(BLOCK_SIZE*CELL_SIZE);
  int num_points = (int) (file_size + CELL_SIZE - 1) / CELL_SIZE;

  short block1[BLOCK_SIZE][3];
  short block2[BLOCK_SIZE][3];

  short x1, y1, z1;
  int cells_read;
  char line[CELL_SIZE];

  int bz = BLOCK_SIZE;
  int sz = num_points;

  for ( size_t ib = 0; ib < num_points; ib += BLOCK_SIZE ) {
    size_t ie = ib + BLOCK_SIZE < num_points ? BLOCK_SIZE : num_points-ib;
    int cells_read = 0;
    while (cells_read < ie && fread(line, 1, CELL_SIZE,file)) {
      block1[cells_read][0] = parse_coord(line);
      block1[cells_read][1] = parse_coord(line+8);
      block1[cells_read][2] = parse_coord(line+16);
      cells_read++;
    }
    for ( size_t jb = 0; jb < num_points-ib; jb += BLOCK_SIZE ) {
      size_t je = jb + BLOCK_SIZE < num_points ? BLOCK_SIZE : num_points-jb;
      if (jb==0) {
        memcpy(block2, block1, sizeof(block1)); 
      } else {
        cells_read = 0;
        while (cells_read < ie && fread(line, 1, CELL_SIZE,file)) {
          block2[cells_read][0] = parse_coord(line);
          block2[cells_read][1] = parse_coord(line+8);
          block2[cells_read][2] = parse_coord(line+16);
          cells_read++;
        }
      }

      for ( size_t ix = 0; ix < ie; ++ix ){
        size_t je_inner = (jb == 0) ? ix : je;
        for ( size_t jx = 0; jx < je_inner; ++jx ) {
          float squared_dist =  (block1[ix][0] - block2[jx][0]) * (block1[ix][0] - block2[jx][0]) 
                              + (block1[ix][1] - block2[jx][1]) * (block1[ix][1] - block2[jx][1]) 
                              + (block1[ix][2] - block2[jx][2]) * (block1[ix][2] - block2[jx][2]);
          int dist = (int)(sqrtf(squared_dist) / 10.0f + 0.5f);
          frequencies[dist]+=1;
        }
      }
    }
    fseek(file, (ib+BLOCK_SIZE) * CELL_SIZE, SEEK_SET);

  }
  fclose(file);


  for( int ix = 1; ix < NUM_DISTANCES; ++ix) {
    if (frequencies[ix] != 0) {
      printf("%05.2f %i\n", ix / 100.0, frequencies[ix]);
    }
  }

  return 0;
}