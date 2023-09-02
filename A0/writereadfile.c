#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MATRIX_FILENAME "matrix.txt"

// Function prototypes
FILE* open_file(const char *mode);
int* allocate_matrix(int size);
void create_matrix(int size);
void read_matrix(int size);

int main() {
    const int matrix_size = 10;
    create_matrix(matrix_size);
    read_matrix(matrix_size);

    printf("Program executed successfully!\n");
    
    return 0;
}

// Function implementations

FILE* open_file(const char *mode) {
    FILE *fp = fopen(MATRIX_FILENAME, mode);
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    return fp;
}

int* allocate_matrix(int size) {
    int* matrix = (int*)malloc(sizeof(int) * size * size);
    if (matrix == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    return matrix;
}

void create_matrix(int size) {
    int* matrix = allocate_matrix(size);
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i * size + j] = i * j;
        }
    }
    
    FILE* fp = open_file("wb");
    fwrite(matrix, sizeof(int), size * size, fp);
    fclose(fp);
    
    free(matrix);
}

void read_matrix(int size) {
    FILE* fp = open_file("rb");
    int* matrix = allocate_matrix(size);
    fread(matrix, sizeof(int), size * size, fp);
    fclose(fp);
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            assert(matrix[i * size + j] == i * j);
        }
    }
    free(matrix);
    printf("File was successfully read! Elements match the expected.\n");
}
