#include <math.h>
#include <stdlib.h>
#include <stdio.h>

static inline void parse_args(int argc, char *argv[], int *num_threads, int *size, int *d) {
int num_threads_set = 0, size_set = 0, d_set = 0;

  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    if (arg[0] == '-') {
      if (arg[1] == 't') {
        *num_threads = strtol(arg + 2, NULL, 10);
        num_threads_set = 1;
      } else if (arg[1] == 'l') {
        *size = strtol(arg + 2, NULL, 10);
        size_set = 1;
      } else {
        printf("Unrecognized option: %s\n", arg);
        printf("Usage: ./newton -t<numberOfThreads> -l<numberOfRows> <degreeOfPolynomial>\n");
        exit(EXIT_FAILURE);
      }
    } else {
      *d = strtol(arg, NULL, 10);
      d_set = 1;
    }
  }

  if (!num_threads_set || !size_set || !d_set) {
    printf("Usage: ./newton -t<numberOfThreads> -l<numberOfRows> <degreeOfPolynomial>\n");
    exit(EXIT_FAILURE);
  }
}


int main(int argc, char *argv[]){
  int num_threads, size, d;
  parse_args(argc, argv, &num_threads, &size, &d);

  // Now, you can use the parsed values as needed in your program.
  // For example:
  printf("Number of threads: %d\n", num_threads);
  printf("Size of grid: %d\n", size);
  printf("Degree of polynomial: %d\n", d);
}