#include "matrix_performance.hh"

void check_transpose(const double* matrix, const int& matrix_dimension) {

  double first_row = 0.0;
  double first_col = 0.0;
  for (int i=0; i<matrix_dimension; i++) {
    for (int j=0; j<matrix_dimension; j++) {
      if (i==0) first_row += matrix[idx(i,j)];
      if (j==0) first_col += matrix[idx(i,j)];
    }    
  }
  cout << "1st row sum = " << first_row << endl;
  cout << "1st col sum = " << first_col << endl;
  
}

void print_matrix(const double* matrix, size_t matrix_dimension) {
  for (int i=0; i< matrix_dimension; i++) {
    for (int j=0; j< matrix_dimension; j++) {
      //cout << matrix[idx(i,j)] << " ";
    } //cout << endl;
  }  
}
