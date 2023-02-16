#include "f2c.h"

int zbesk_(doublereal *zr, doublereal *zi, doublereal *fnu, integer *kode,
           integer *n, doublereal *cyr, doublereal *cyi, integer *nz,
           integer *ierr);

double kode(double nu, double z, long kode) {
  double zi = 0;
  long n = 1;
  double cyr;
  double cyi;
  long nz;
  long ierr;
  int ret = zbesk_(&z, &zi, &nu, &kode, &n, &cyr, &cyi, &nz, &ierr);
  return cyr;
}

extern double kve(double nu, double z) { return kode(nu, z, 2); }
extern double kv(double nu, double z) { return kode(nu, z, 1); }
