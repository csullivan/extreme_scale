#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
extern "C" {
  #include "dummy.h"
}

int main(int argc, char *argv[]) {
  // arrays
  int nk = 1;
  int n = 1e6;
  int i, k;
  if (argc > 1) nk = atoi(argv[1]);
  //auto a = new double[n]();
  //auto c = new double[n]();
  auto a = (double*)malloc(n*sizeof(double));
  auto c = (double*)malloc(n*sizeof(double));
  // timers
  struct timeval tprogStart, tprogEnd;
  struct timeval tStart, tEnd;
  
  // avoid cold start by performing one iteration before main nk loops
  double tperformance = 0.0;
  gettimeofday(&tprogStart,NULL);
  for (k=0; k<1; k++) {
    gettimeofday(&tStart,NULL);
    for (i=0; i<n; i++) {
      c[i] = a[i];
    }
    gettimeofday(&tEnd,NULL);
    tperformance += (tEnd.tv_sec - tStart.tv_sec) + 1.0e-6 * (tEnd.tv_usec - tStart.tv_usec);
    dummy(a,c);
  }
  gettimeofday(&tprogEnd,NULL);
  // end cold start prep

  // begin real test
  tperformance = 0.0;
  gettimeofday(&tprogStart,NULL);
  for (k=0; k<nk; k++) {
    gettimeofday(&tStart,NULL);
    for (i=0; i<n; i++) {
      c[i] = a[i];
    }
    gettimeofday(&tEnd,NULL);
    tperformance += (tEnd.tv_sec - tStart.tv_sec) + 1.0e-6 * (tEnd.tv_usec - tStart.tv_usec);
    dummy(a,c);
  }
  gettimeofday(&tprogEnd,NULL);
  // end real test

  std::cout << "Time for loop (s): "<< std::scientific << tperformance/nk<< std::endl;
  std::cout << "Total time (s): "<< (tprogEnd.tv_sec - tprogStart.tv_sec) + 1.0e-6 * (tprogEnd.tv_usec - tprogStart.tv_usec) << std::endl;
  
  return 0;
}
