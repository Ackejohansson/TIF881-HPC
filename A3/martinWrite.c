#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
  const int bz = 5;
  const int sz = 10; 
  const int maxv = 255;
  int pix_size = 12;

  unsigned char *vs = malloc(sz*sizeof(unsigned char));
  for (int ix = 0; ix < sz; ix++)
    vs[ix] = (unsigned char) (rand() * maxv);
  
  char ss[maxv+1][pix_size+1];
  for (int ix = 0; ix <= maxv; ix++)
    sprintf(ss[ix], "%03i %03i %03i ", ix, ix, ix);
  
  FILE *f = fopen("tmp", "w");

  char buf[pix_size*sz];
  for (int ix = 0; ix < bz; ix++){
    for (int jx = 0; jx < sz; jx++){
      // printf("%s\n", ss[vs[jx]]);
      memcpy(buf + pix_size*jx, ss[vs[jx]], pix_size);
    }
    //printf("%d %d %d", buf[0], buf[1], buf[2]);
    fwrite(buf, pix_size, sz, f);
  }
  free(vs);
  fclose(f);
}