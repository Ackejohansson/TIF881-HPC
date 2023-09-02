#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

FILE* open_file(char *mode){
    FILE *fp = fopen("matrix.txt", mode);
    if (fp == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    return fp;
}

void create_matrix(int size){
  int *matrix = (int*)malloc(sizeof(int) * size * size);
  
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; ++j) {
      matrix[i*size + j] = i * j;
    }
  }
  FILE* fp = open_file("wb");
  fwrite(matrix, sizeof(int), size * size, fp);
  fclose(fp);
  free(matrix);
}

void read_matrix(int size){
  FILE* fp = open_file("rb");
  int *matrix = (int*)malloc(sizeof(int)*size*size);
  fread(matrix, sizeof(int), size * size, fp);
  fclose(fp);
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      assert(matrix[i*size + j] == i*j);
    }
  }
  printf("File was sucessfully created!!\n");
  free(matrix);
}

int main() {
  const int matrix_size = 10;
  create_matrix(matrix_size);
  read_matrix(matrix_size);
  return 0;
}