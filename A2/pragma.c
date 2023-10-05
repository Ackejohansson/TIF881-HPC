#include <stdio.h>
#include <omp.h>

int main() {
    const int n = 1000000; // Number of elements in the array
    int sum[n]; // Array to store the values

    int num_threads = 4; // Set the number of threads
    omp_set_num_threads(num_threads); // Explicitly set the number of threads

    // Initialize the array
    for (int i = 0; i < n; ++i) {
        sum[i] = 0;
    }

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        sum[i] += 1;
    }

    // Print the results
    printf("Updated array elements:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", sum[i]);
    }
    printf("\n");

    return 0;
}
