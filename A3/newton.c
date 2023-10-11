#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>

typedef int TYPE_ATTR;
typedef short TYPE_CONV;

typedef struct {
  int val;
  char pad[60]; // cacheline - sizeof(int)
} int_padded;

typedef struct {
  TYPE_ATTR **attractors;
  TYPE_CONV **convergence;
  int ib;
  int istep;
  int sz;
  int tx;
  mtx_t *mtx;
  cnd_t *cnd;
  int_padded *status;
} thrd_info_t;

typedef struct {
  TYPE_ATTR **attractors;
  TYPE_CONV **convergence;
  float **w;
  int sz;
  int nthrds;
  mtx_t *mtx;
  cnd_t *cnd;
  int_padded *status;
} thrd_info_check_t;

static inline double complex fofx(double complex x, int d){
  return cpow(x, d) - 1.0;
}

static inline double complex fprimeofx(double complex x, int d){
  return d * cpow(x, d - 1);
}

static inline void compute_distances(int size, int d, TYPE_ATTR *attractor){
  double tol = 1e-6;
  int max_iter = 128;
  double complex x_new, x_old;
  double a = (double)i/size-2.0;
  for (int j = 0; j < size; j++){
    int iter = 0;
    x_old = a - ((double)j/size+2.0)*I;
    for(iter; i < max_iter; i++){
      x_new = x_old - fofx(x_old, d)/fprimeofx(x_old, d);
      
      if (cabs(fofx(x_new, d)) < 1e-3) {
        break;
      }
      if (cabs(creal(x_new)) > 1e10 || cabs(cimag(x_new)) > 1e10) {
        break;
      }
      x_old = x_new;
    }
    attractor[j] = x_new;
    convergence[j] = iter;
  }
}

int main_thrd(void *args){
  const thrd_info_t *thrd_info = (thrd_info_t*) args;
  TYPE_ATTR **attractors = thrd_info->attractors;
  TYPE_CONV **convergences = thrd_info->convergences;
  const int ib = thrd_info->ib;
  const int istep = thrd_info->istep;
  const int sz = thrd_info->sz;
  const int tx = thrd_info->tx;
  mtx_t *mtx = thrd_info->mtx;
  cnd_t *cnd = thrd_info->cnd;
  int_padded *status = thrd_info->status;

  for ( int ix = ib; ix < sz; ix += istep ) {
    TYPE_ATTR *attractor = (TYPE_ATTR*) malloc(sz*sizeof(TYPE_ATTR));
    TYPE_CONV *convergence = (TYPE_CONV*) malloc(sz*sizeof(TYPE_CONV));
    for ( size_t cx = 0; cx < size; ++cx ) {
      attractor[cx] = 0;
      convergence[cx] = 0;
    }
    compute_distances(sz, ix, attractor, convergence);

    mtx_lock(mtx);
    attractors[ix] = attractor;
    status[tx].val = ix + istep;
    mtx_unlock(mtx);
    cnd_signal(cnd);
  }

  return 0;
}

int main_thrd_check(void *args){
  const thrd_info_check_t *thrd_info = (thrd_info_check_t*) args;
  const TYPE_ATTR **attractors = thrd_info->attractors;
  const TYPE_CONV **convergences = thrd_info->convergences;
  const int sz = thrd_info->sz;
  const int nthrds = thrd_info->nthrds;
  mtx_t *mtx = thrd_info->mtx;
  cnd_t *cnd = thrd_info->cnd;
  int_padded *status = thrd_info->status;

  for ( int ix = 0, ibnd; ix < sz; ) {
    // Compute min if new row available
    for ( mtx_lock(mtx); ; ) {
      ibnd = sz;
      for ( int tx = 0; tx < nthrds; ++tx )
        if ( ibnd > status[tx].val )
          ibnd = status[tx].val;

      if ( ibnd <= ix )
        cnd_wait(cnd,mtx);
      else {
        mtx_unlock(mtx);
        break;
      }
    }

    fprintf(stderr, "checking until %i\n", ibnd);
    // Perform check 
    // Here we can write to file if ibnd is larger than threshold
    for ( ; ix < ibnd; ++ix )
      free(w[ix]);
  }

  return 0;
}



int main(int argc, char *argv[]){
  const int sz = 50;
  TYPE_ATTR **attractors = (TYPE_ATTR**) malloc(sz*sizeof(TYPE_ATTR*));
  TYPE_CONV **convergences = (TYPE_CONV**) malloc(sizeof(TYPE_CONV*)*size);

  const int nthrds = 8;
  thrd_t thrds[nthrds];
  thrd_info_t thrds_info[nthrds];

  thrd_t thrd_check;
  thrd_info_check_t thrd_info_check;
  
  mtx_t mtx;
  mtx_init(&mtx, mtx_plain);

  cnd_t cnd;
  cnd_init(&cnd);

  int_padded status[nthrds];

  for ( int tx = 0; tx < nthrds; ++tx ) {
    thrds_info[tx].attractors = attractors;
    thrds_info[tx].convergences = convergences;
    thrds_info[tx].ib = tx;
    thrds_info[tx].istep = nthrds;
    thrds_info[tx].sz = sz;
    thrds_info[tx].tx = tx;
    thrds_info[tx].mtx = &mtx;
    thrds_info[tx].cnd = &cnd;
    thrds_info[tx].status = status;
    status[tx].val = -1;

    int r = thrd_create(thrds+tx, main_thrd, (void*) (thrds_info+tx));
    if ( r != thrd_success ) {
      fprintf(stderr, "failed to create thread\n");
      exit(1);
    }
    thrd_detach(thrds[tx]);
  }

  {
    thrd_info_check.attractors = attractors;
    thrd_info_check.sz = sz;
    thrd_info_check.nthrds = nthrds;
    thrd_info_check.mtx = &mtx;
    thrd_info_check.cnd = &cnd;
    thrd_info_check.status = status;
    int r = thrd_create(&thrd_check, main_thrd_check, (void*) (&thrd_info_check));
    if ( r != thrd_success ) {
      fprintf(stderr, "failed to create thread\n");
      exit(1);
    }
  }

  {
    int r;
    thrd_join(thrd_check, &r);
  }

  free(ventries);
  free(v);
  free(w);

  mtx_destroy(&mtx);
  cnd_destroy(&cnd);

  return 0;
}