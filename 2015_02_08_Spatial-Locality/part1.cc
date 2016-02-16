#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <iomanip>

/* Column-major order (Same as Fortran). 
   This means consecutive elements in a column are 
   stored in contiguous memory. */
#define idx(a,b) ((b)*matrix_dimension+a)
#define STREAM_COPY (41539100000)

using namespace std;


int main( int argc, char **argv ) {
  int matrix_dimension = 1000;
  int trials = 100;

  // input parser
  if (argc > 1) {
    matrix_dimension = atoi(argv[1]);
    if (argc == 3) {
      trials = atoi(argv[2]);
    }
  }
  
  int n = matrix_dimension*matrix_dimension;
  auto matrixA = (double*)calloc(n,sizeof(double));
  auto matrixB = (double*)calloc(n,sizeof(double));


  // clock resolution
  auto clockres = 1.0/chrono::high_resolution_clock::period::den;
  
  // warm-up
  auto start = chrono::high_resolution_clock::now();  
  for(int i=0;i<matrix_dimension;i++){
    for(int j=0;j<matrix_dimension;j++){
      // jth iteration of matrix A has spatial locality
      // jth iteration of matrix B has to load each column into cache every write
      matrixB[idx(i,j)] = matrixA[idx(j,i)];
    }
  }
  auto stop = chrono::high_resolution_clock::now();
  double tperformance =
    chrono::duration_cast<chrono::microseconds>(stop - start).count();    
  // end warm-up
  
  // ----------------------------------------------------------------------

  tperformance = 0.0;
  for (int n=0;n<trials;n++) {
    start = chrono::high_resolution_clock::now();  
    for(int i=0;i<matrix_dimension;i++){
      for(int j=0;j<matrix_dimension;j++){
	matrixB[idx(i,j)] = matrixA[idx(j,i)];
      }
    }
    stop = chrono::high_resolution_clock::now();
    tperformance +=
      chrono::duration_cast<chrono::microseconds>(stop - start).count();
  }

  // ----------------------------------------------------------------------
  
  tperformance = tperformance*1e-6/trials;
  cout << "Array size (n), Time for loop (s), Prediction (s): ";
  cout << setw(7) << matrix_dimension <<" "<< scientific << setprecision(3);
  cout  << tperformance << " ";
  double rwtime = sizeof(double)*(1.0/STREAM_COPY);
  cout  << matrix_dimension*matrix_dimension*(2*rwtime) << " ";
  int L = 8; // assuming cacheline holds 64 bytes 8 = 64 / sizeof(dble)
  cout  << matrix_dimension*matrix_dimension*(rwtime+L*rwtime) << " ";
  cout<< endl;

  
  return 0;
}
