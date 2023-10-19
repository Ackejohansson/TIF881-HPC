#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
  const int bz = 50;
  const int sz = 10; 
  const int maxv = 255;
  int pix_size = 12;

  // unsigned char *vs = malloc(sz*sizeof(unsigned char));
  
  char ss[maxv+1][pix_size];
  for (int ix = 0; ix <= maxv; ix++)
    sprintf(ss[ix], "%03i %03i %03i ", ix, ix, ix);
  
  FILE *f = fopen("tmp", "w");

  char buf[pix_size*sz];
  for (int ix = 0; ix < bz; ix++){
    for (int jx = 0; jx < sz; jx++){
      unsigned char vs = (unsigned char) (rand() * maxv);
      memcpy(buf + pix_size*jx, ss[vs], pix_size);
    }
    fwrite(buf, pix_size, sz, f);
  }
  
  fclose(f);
}