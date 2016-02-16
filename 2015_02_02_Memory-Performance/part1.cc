#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <iomanip>

extern "C" {
  #include "dummy.h"
}

using namespace std;

int main(int argc, char *argv[]) {

  // array declarations
  int nk = 1;
  int n = 1e6;
  if (argc > 2) {
    n = atoi(argv[1]);
    nk = atoi(argv[2]);
  }
  // I noticed an interesting decrease in performance
  // when using the c++ new keyword instead of malloc.
  // Otherwise, this and a bare c program with the same  
  // functionality are 1 to 1 in performance.
  //auto a = new double[n]();
  //auto c = new double[n]();
  auto a = (double*)malloc(n*sizeof(double)); 
  auto c = (double*)malloc(n*sizeof(double));

  // clock resolution
  auto clockres = 1.0/chrono::high_resolution_clock::period::den;
  //  if (n==250) cout << "Clock resolution: " << clockres << " (ticks/s)" <<endl;

  // ------------------------------------------------------------------------------------
  
  // avoid cold start by performing one iteration before main test
  double tperformance = 0.0;
  auto fullstart = chrono::high_resolution_clock::now();
  for (int k=0; k<1; k++) {
    auto start = chrono::high_resolution_clock::now();
    for (int i=0; i<n; i++) {
      c[i] = a[i];
    }
    auto stop = chrono::high_resolution_clock::now();
    tperformance += chrono::duration_cast<chrono::microseconds>(stop - start).count();    
    dummy(a,c);
  }
  auto fullstop = chrono::high_resolution_clock::now();
  // end cold start prep

  // ------------------------------------------------------------------------------------
  
  // begin real test
  tperformance = 0.0;
  fullstart = chrono::high_resolution_clock::now();
  for (int k=0; k<nk; k++) {
    auto start = chrono::high_resolution_clock::now();
    for (int i=0; i<n; i++) {
      c[i] = a[i];
    }
    auto stop = chrono::high_resolution_clock::now();
    tperformance += chrono::duration_cast<chrono::microseconds>(stop - start).count();
    dummy(a,c);
  }
  fullstop = chrono::high_resolution_clock::now();
  // end real test

  // ------------------------------------------------------------------------------------

  tperformance = tperformance/nk*1e-6;
  cout << "Array size (n), Time for loop (s), Rate (GB/s), Total time (s):   ";
  cout << setw(7) << n <<" "<< scientific << setprecision(3) << tperformance << " ";
  cout << std::fixed << n*2*sizeof(double)/tperformance * 1e-9 << " ";
  cout << chrono::duration_cast<chrono::microseconds>(fullstop - fullstart).count()*1e-6 << endl;
  
  return 0;
}
