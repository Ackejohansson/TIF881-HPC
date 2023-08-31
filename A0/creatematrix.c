#include <stdio.h>


int main() {
    FILE *f = fopen("matrix.txt", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    const int size = 10;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            fprintf(f, "%d ", i * j);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    return 0;
}