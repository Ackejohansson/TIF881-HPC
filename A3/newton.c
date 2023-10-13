#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <complex.h>

typedef int TYPE_ATTR;
typedef short TYPE_CONV;

typedef struct {
  int val;
  char pad[60]; // cacheline - sizeof(int)
} int_padded;

typedef struct {
  TYPE_ATTR **attractors;
  TYPE_CONV **convergences;
  int ib;
  int istep;
  int sz;
  int tx;
  int d;
  mtx_t *mtx;
  cnd_t *cnd;
  int_padded *status;
} thrd_info_t;

typedef struct {
  TYPE_ATTR **attractors;
  TYPE_CONV **convergences;
  float **w;
  int sz;
  int nthrds;
  int d;
  mtx_t *mtx;
  cnd_t *cnd;
  int_padded *status;
} thrd_info_check_t;


static inline void parse_args(int argc, char *argv[], int *nthrds, int *size, int *d) {
  if (argc != 4) {
    printf("Usage: newton -t<numberOfThreads> -l<numberOfLines> <degreeOfPolynomial>\n");
    exit(EXIT_FAILURE);
  }
  int num_threads_set = 0, size_set = 0, d_set = 0;

  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    if (arg[0] == '-') {
      if (arg[1] == 't') {
        *nthrds = strtol(arg + 2, NULL, 10);
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


static inline double complex fofx(double complex x, int d){
  return cpow(x, d) - 1.0;
}

static inline double complex fprimeofx(double complex x, int d){
  return d * cpow(x, d - 1);
}

static inline void compute_distances(int size, int d, int ix, TYPE_ATTR *attractor, TYPE_CONV *convergence){
  double tol = 1e-6;
  int max_iter = 128;
  double complex x_new, x_old;

  double a = (double)ix/size - 2.0;
  for ( int j = 0; j < size; j++){
    int iter;
    x_old = a + ((double)j/size+2.0)*I;
    for ( iter = 0; iter < max_iter; iter++){
      x_new = x_old - fofx(x_old, d)/fprimeofx(x_old, d);
      printf("x_new = %f + %fi\n", creal(x_new), cimag(x_new));
      
      if (cabs(fofx(x_new, d)) < 1e-3) {
        break;
      }
      if (cabs(creal(x_new)) > 1e10 || cabs(cimag(x_new)) > 1e10) {
        break;
      }
      x_old = x_new;
    }
    //attractor[j] = x_new;
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
  const int d = thrd_info->d;
  mtx_t *mtx = thrd_info->mtx;
  cnd_t *cnd = thrd_info->cnd;
  int_padded *status = thrd_info->status;

  for ( int ix = ib; ix < sz; ix += istep ) {
    TYPE_ATTR *attractor =   (TYPE_ATTR*) malloc(sz*sizeof(TYPE_ATTR));
    TYPE_CONV *convergence = (TYPE_CONV*) malloc(sz*sizeof(TYPE_CONV));
    if ( attractor == NULL || convergence == NULL ) {
      perror("Memory allocation failed");
      exit(EXIT_FAILURE);
    }
    for  ( int jx = 0; jx < sz; ++jx ){
      attractor[jx] = 0;
      convergence[jx] = 0;
    }

    compute_distances(sz, d, ix, attractor, convergence);

    mtx_lock(mtx);
    attractors[ix] = attractor;
    convergences[ix] = convergence;
    status[tx].val = ix + istep;
    mtx_unlock(mtx);
    cnd_signal(cnd);
  }

  return 0;
}

int main_thrd_check(void *args){
  const thrd_info_check_t *thrd_info = (thrd_info_check_t*) args;
  const TYPE_ATTR *const *attractors = (const TYPE_ATTR *const *)thrd_info->attractors;
  const TYPE_CONV *const *convergences = (const TYPE_CONV *const *)thrd_info->convergences;
  const int sz = thrd_info->sz;
  const int nthrds = thrd_info->nthrds;
  mtx_t *mtx = thrd_info->mtx;
  cnd_t *cnd = thrd_info->cnd;
  int_padded *status = thrd_info->status;

  FILE* fp = open_file("newton_convergence_xd.ppm", "w");
  if (fp == NULL) {
    perror("Failed to open the file");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "P3\n");
  fprintf(fp, "%d %d\n", sz, sz);
  fprintf(fp, "255\n");

  for ( int ix = 0, ibnd; ix < sz; ) {
    // Compute min if new row available
    for ( mtx_lock(mtx); ; ) {
      ibnd = sz;
      for ( int tx = 0; tx < nthrds; ++tx )
        if ( ibnd > status[tx].val )
          ibnd = status[tx].val;

      if ( ibnd > ix ){
        mtx_unlock(mtx);
        break;
      }
      cnd_wait(cnd,mtx);
    }
    fprintf(stderr, "checking until %i\n", ibnd);

    for ( ; ix < ibnd; ++ix ){
      for (int jx = 0; jx < sz; ++jx)
        unsigned char scaledValue = (unsigned char)((convergences[ix][jx] - 1) * 255 / 127);
        fprintf(fp, "%d %d %d ", scaledValue, scaledValue, scaledValue);
      fprintf(fp, "\n");
      free((void *)attractors[ix]);
      free((void *)convergences[ix]);
    }
  }
  fclose(fp);
  return 0;
}



int main(int argc, char *argv[]){
  int nthrds, sz, d;
  parse_args(argc, argv, &nthrds, &sz, &d);

  TYPE_ATTR **attractors = (TYPE_ATTR**) malloc(sz*sizeof(TYPE_ATTR*));
  TYPE_CONV **convergences = (TYPE_CONV**) malloc(sz*sizeof(TYPE_CONV*));
  if ( attractors == NULL || convergences == NULL ) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }

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
    thrds_info[tx].d = d;
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
    thrd_info_check.convergences = convergences;
    thrd_info_check.sz = sz;
    thrd_info_check.nthrds = nthrds;
    thrd_info_check.d = d;
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

  free(attractors);
  free(convergences);
  mtx_destroy(&mtx);
  cnd_destroy(&cnd);

  return 0;
}