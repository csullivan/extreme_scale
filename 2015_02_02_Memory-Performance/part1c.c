#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include "dummy.h"

int main(int argc, char *argv[]) {
  struct timeval tprogStart, tprogEnd;

  
  int n = 1e6;
  int nk = 1;
  int i,k;
  if (argc > 1) nk = atoi(argv[1]);
  double* a = (double*)malloc(n*sizeof(double));
  double* c = (double*)malloc(n*sizeof(double));
  struct timeval tStart, tEnd;

  // avoid cold start
  double total = 0.;
  gettimeofday(&tprogStart,NULL);
  for (k=0; k<1; k++) {
    gettimeofday(&tStart,NULL);
    for (i=0; i<n; i++) {
      c[i] = a[i];
    }
    gettimeofday(&tEnd,NULL);
    total += (tEnd.tv_sec - tStart.tv_sec) + 1.0e-6 * (tEnd.tv_usec - tStart.tv_usec);
    dummy(a,c);
  }
  gettimeofday(&tprogEnd,NULL);
  // end cold start
  
  total = 0.;
  gettimeofday(&tprogStart,NULL);
  for (k=0; k<nk; k++) {
    gettimeofday(&tStart,NULL);
    for (i=0; i<n; i++) {
      c[i] = a[i];
    }
    gettimeofday(&tEnd,NULL);
    total += (tEnd.tv_sec - tStart.tv_sec) + 1.0e-6 * (tEnd.tv_usec - tStart.tv_usec);
    dummy(a,c);
  }
  gettimeofday(&tprogEnd,NULL);
  printf("Time for loop (s): %e\n",total/nk);
  printf("Total time: %e\n", (tprogEnd.tv_sec - tprogStart.tv_sec) + 1.0e-6 * (tprogEnd.tv_usec - tprogStart.tv_usec));
  
  return 0;
}
