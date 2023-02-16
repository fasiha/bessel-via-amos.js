#include "f2c.h"
#include <stdio.h>

int zbesk_(doublereal *zr, doublereal *zi, doublereal *fnu, integer *kode,
           integer *n, doublereal *cyr, doublereal *cyi, integer *nz,
           integer *ierr);

int main() {
  // inputs
  double zr = 3.3;
  double zi = 0.0;
  double fnu = 4.4;
  long kode = 2;
  long n = 1;

  // outputs
  double cyr;
  double cyi;
  long nz;
  long ierr;

  // call
  int ret = zbesk_(&zr, &zi, &fnu, &kode, &n, &cyr, &cyi, &nz, &ierr);

  // output
  printf("ret=%d\n", ret);
  printf("cyr=%f\n", cyr);
  printf("cyi=%f\n", cyi);
  printf("nz=%ld\n", nz);
  printf("ierr=%ld\n", ierr);

  return 0;
}