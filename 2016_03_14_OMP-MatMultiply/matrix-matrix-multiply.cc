#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include "matrix_performance.hh"




int main( int argc, char **argv ) {
  int matrix_dimension = 1000;
  int trials = 1;

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
      
      matrixA[idx(i,j)] = i+1;
      matrixB[idx(i,j)] = i+1;	
    }
  }

  print_matrix(matrixA,matrix_dimension);

  auto matrixC1 = basic_matrix_multiply(matrixA,matrixB,matrix_dimension,trials);
  print_matrix(matrixC1,matrix_dimension);

  //auto matrixC2 = blocked_matrix_multiply(16,matrixA,matrixB,matrix_dimension,trials);
  //cout << endl;
  //print_matrix(matrixC2,matrix_dimension);
  
  return 0;
}
