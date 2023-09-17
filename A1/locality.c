void
row_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs){
  for ( size_t ix = 0; ix < nrs; ++ix ) {
    double sum = 0.;
    for ( size_t jx = 0; jx < ncs; ++jx )
      sum += matrix[ix][jx];
    sums[ix] = sum;
  }
}

void col_sums(double * sums, const double ** matrix, size_t nrs, size_t ncs){
  for ( size_t jx = 0; jx < ncs; ++jx ) {
    double sum = 0.;
    for ( size_t ix = 0; ix < nrs; ++ix )
      sum += matrix[ix][jx];
    sums[jx] = sum;
  }
}

int main(){
    const size_t nrs = 30000;
    return 0;
}