#include <stdio.h>
#include <stdlib.h>

void create_matrix(){
    FILE *f = fopen("matrix.txt", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    const int size = 10;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            fprintf(f, "%d ", i * j);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void read_matrix(){
    FILE *f = fopen("matrix.txt", "r");
    if (f == NULL) {
      printf("Error opening file!\n");
      exit(1);
    }

    const int size = 10;
    int value;

    for (int i = 0; i < size; i++){
      for (int j = 0; j < size; j++){
        // Saves the value read from the file in the variable value
        fscanf(f, "%d", &value);
        // Checks if the value read is equal to i * j
        if (value != i * j){
          printf("Error reading file!\n");
          exit(1);
        }
      }
    }
    printf("File read successfully!\n");
}


int main() {
    create_matrix();
    read_matrix();
    return 0;
}
