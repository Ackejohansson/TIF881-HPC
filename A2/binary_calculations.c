#include <stdio.h>

// Function to add two numbers stored in memory as doubles
void addNumbers(char* num1_mem, char* num2_mem) {
    double num1, curr_num, result;
    
    // Interpret memory blocks as doubles
    sscanf(num1_mem, "%lf", &num1);
    for (int i=1; i<3; ++i){
      sscanf(num2_mem, "%lf", &curr_num);

    }

    // Perform the addition
    result = num1 + curr_num;

    // Format the result back into the memory block
    sprintf(num1_mem, "%.3lf", result);
}

int main() {
    char num1_mem[] = "+00.001";
    char num2_mem[] = "-03.020";
    char num2_mem[] = "-03.020";

    addNumbers(num1_mem, num2_mem);

    printf("Result: %s\n", num1_mem);  // This will print: "Result: -03.019"

    return 0;
}
