#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  const int size = 30000;
  double as_re[size], as_im[size], bs_re[size], bs_im[size], cs_re[size], cs_im[size];

  for (int i = 0; i < size; i++) {
    bs_re[i] = (double)rand()/RAND_MAX;
    bs_im[i] = (double)rand()/RAND_MAX;
    cs_re[i] = (double)rand()/RAND_MAX;
    cs_im[i] = (double)rand()/RAND_MAX;
  }

  for (int i = 0; i < size; i++) {
    as_re[i] = (bs_re[i] * cs_re[i]) - (bs_im[i] * cs_im[i]);
    as_im[i] = (bs_re[i] * cs_im[i]) + (bs_im[i] * cs_re[i]);
  }

  int random_index = rand() % size;
  printf("Result at index %d: %lf + %lfi\n", random_index, as_re[random_index], as_im[random_index]);

  return 0;
}
