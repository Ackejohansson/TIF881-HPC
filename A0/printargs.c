#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int processArguments(int argc, char *argv[], int *a, int *b) {
    int option;
    bool aInitialized = false; bool bInitialized = false;
    while ((option = getopt(argc, argv, "a:b:")) != -1) {
        switch (option) {
            case 'a':
                *a = atoi(optarg);
                aInitialized = true;
                break;
            case 'b':
                *b = atoi(optarg);
                aInitialized = true;
                break;
            default:
                return 1;
        }
    }
    if (!aInitialized || !bInitialized) {
        printf("Both -a and -b options with integer values are required.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int a = 0; int b = 0;

    if (processArguments(argc, argv, &a, &b) != 0) {
        printf("Usage: -a <int1> -b <int2>\n");
        return 1;
    }

    printf("A is %d and B is %d\n", a, b);
    return 0;
}
