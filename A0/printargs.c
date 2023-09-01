#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_VARIABLES 2

int processArguments(int argc, char *argv[], int variables[], bool initialized[]) {
    int option;
    for (int i = 0; i < NUM_VARIABLES; i++) {
        initialized[i] = false;
    }

    while ((option = getopt(argc, argv, "a:b:")) != -1) {
        for (int i = 0; i < NUM_VARIABLES; i++) {
            if (option == 'a' + i) {
                variables[i] = atoi(optarg);
                initialized[i] = true;
                break;
            }
        }
    }

    for (int i = 0; i < NUM_VARIABLES; i++) {
        if (!initialized[i]) {
            printf("Option -%c was not specified.\n", 'a' + i);
            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int variables[NUM_VARIABLES];
    bool initialized[NUM_VARIABLES];

    if (processArguments(argc, argv, variables, initialized) != 0) {
        printf("Usage: -a<int1> -b<int2> ... -j<int10>\n");
        return 1;
    }

    for (int i = 0; i < NUM_VARIABLES; i++) {
        printf("Variable %c is %d\n", 'A' + i, variables[i]);
    }

    return 0;
}
