#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include "transpose.hh"




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

  for (int i=0; i<matrix_dimension; i++) {
    for (int j=0; j<matrix_dimension; j++) {
      if (i == 0) {
	matrixA[idx(i,j)] = 1.0;
      }
    }
  }

  // clock resolution
  auto clockres = 1.0/chrono::high_resolution_clock::period::den;

  // check_transpose(matrixA,matrix_dimension);
  // basic_transpose(matrixA,matrixB,matrix_dimension,trials);
  // check_transpose(matrixB,matrix_dimension);

  //check_transpose(matrixA,matrix_dimension);
  blocked_transpose(16,matrixA,matrixB,matrix_dimension,trials);
  //check_transpose(matrixB,matrix_dimension);
  
  return 0;
}
