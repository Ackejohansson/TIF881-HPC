#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MATRIX_FILENAME "matrix.txt"
#define SIZE 10 // Matrix size

// Function prototypes
FILE* open_file(const char *mode);
int* allocate_matrix();
void create_matrix();
void read_matrix();

int main() {
    create_matrix();
    read_matrix();
    return 0;
}

// Function implementations
FILE* open_file(const char *mode) {
    FILE *fp = fopen(MATRIX_FILENAME, mode);
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    return fp;
}

int* allocate_matrix() {
    int* matrix = malloc(sizeof(int) * SIZE * SIZE);
    if (matrix == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    return matrix;
}

void create_matrix() {
    int* matrix = allocate_matrix();
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i * SIZE + j] = i * j;
        }
    }
    
    FILE* fp = open_file("wb");
    fwrite(matrix, sizeof(int), SIZE * SIZE, fp);
    fclose(fp);
    free(matrix);
}

void read_matrix() {
  FILE* fp = open_file("cells");
  int* matrix = allocate_matrix(SIZE);
  
  fread(matrix, sizeof(int), SIZE * SIZE, fp);
  fclose(fp);
  
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      assert(matrix[i * SIZE + j] == i * j);
    }
  }
  free(matrix);
  printf("File was successfully read! Elements match the expected.\n");
}
