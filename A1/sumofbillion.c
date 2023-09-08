#include <stdio.h>
#include <time.h>

int main() {
  long long int sum = 0;
  int billion = 1000000000;

  clock_t start_time = clock();
  for (int i = 0; i <= billion; i++){
      sum += i;
  }
  clock_t end_time = clock();

  printf("Execution time: %f seconds\n", (double)(end_time-start_time)/CLOCKS_PER_SEC);
  fprintf(stdout, "%lld\n", sum);
  return 0;
}
