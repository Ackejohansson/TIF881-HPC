#include <stdlib.h>
#include <stdio.h>


void initLinearIndex(size_t* p, size_t size){
  for (size_t ix = 0; ix<size; ++ix)
    p[ix] = ix;
}

void initJumpIndex(size_t* p, size_t size) {
  size_t size_jump = 1000;
  for (size_t jx = 0, kx = 0; jx < size_jump; ++jx)
    for (size_t ix = jx; ix < size; ix += size_jump, ++kx)
      p[ix] = kx;
}

int main(){
  size_t size = 1000000;
  double* x = (double*) malloc(size*sizeof(double));
  double* y = (double*) malloc(size*sizeof(double));
  size_t* p = (size_t*) malloc(size*sizeof(size_t));
  double a = 0.5;

  if (x == NULL || y == NULL || p == NULL){
    printf("Error allocating memory\n");
    return 1;
  }
  for(size_t ix = 0; ix < size; ++ix){
    x[ix] = (double)rand()/RAND_MAX;
    y[ix] = (double)rand()/RAND_MAX;
  }

  // Choose which init function to use
  initLinearIndex(p, size);
  //initJumpIndex(p, size);


  for ( size_t kx = 0; kx < size; ++kx ) {
    size_t jx = p[kx];
    y[jx] += a * x[jx];
  }

  printf("Random element of y: %lf\n", y[500]);

  free(x);
  free(y);
  free(p);
  return 0;
}