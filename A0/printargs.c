#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int processArguments(int argc, char *argv[], int *a, int *b) {
    int option;
    while ((option = getopt(argc, argv, "a:b:")) != -1) {
        switch (option) {
            case 'a':
                *a = atoi(optarg);  // Convert the string argument to an integer
                break;
            case 'b':
                *b = atoi(optarg);  // Convert the string argument to an integer
                break;
            default:
                return 1;
        }
    }
    if (*a == 0 || *b == 0) {
        printf("Both -a and -b options with integer values are required.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int a = 0;
    int b = 0;

    if (processArguments(argc, argv, &a, &b) != 0) {
        printf("Usage: -a <int1> -b <int2>\n");
        return 1;
    }

    printf("A is %d and B is %d\n", a, b);

    return 0;
}
