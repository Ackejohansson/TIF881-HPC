#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mul_cpx(
  double *a_re,
  double *a_im,
  double *b_re,
  double *b_im,
  double *c_re,
  double *c_im
) {
  *a_re = (*b_re * *c_re) - (*b_im * *c_im);
  *a_im = (*b_re * *c_im) + (*b_im * *c_re);
}

int main() {
  srand(time(NULL));

  const int size = 30000;
  double as_re[size], as_im[size], bs_re[size], bs_im[size], cs_re[size], cs_im[size];

  // Initialize bs_re, bs_im, cs_re, and cs_im with random values
  for (int i = 0; i < size; i++) {
      bs_re[i] = (double)rand() / RAND_MAX;
      bs_im[i] = (double)rand() / RAND_MAX;
      cs_re[i] = (double)rand() / RAND_MAX;
      cs_im[i] = (double)rand() / RAND_MAX;
  }

  // Multiply bs and cs using mul_cpx 30,000 times
  for (int i = 0; i < size; i++) {
      mul_cpx(&as_re[i], &as_im[i], &bs_re[i], &bs_im[i], &cs_re[i], &cs_im[i]);
  }

  // Print one random entry from as
  int random_index = rand() % size;
  printf("Result at index %d: %lf + %lfi\n", random_index, as_re[random_index], as_im[random_index]);

  return 0;
}
