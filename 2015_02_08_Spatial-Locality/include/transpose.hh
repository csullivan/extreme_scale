#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>

/* Column-major order (Same as Fortran). 
   This means consecutive elements in a column are 
   stored in contiguous memory. */
#define idx(a,b) ((b)*matrix_dimension+a)
#define STREAM_COPY (41539100000)



using namespace std;


inline void basic_transpose(const double* matrixA, double *matrixB, const int& matrix_dimension, const int& trials) {

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

}

inline void blocked_transpose(const int& blocksize,
			      const double* matrixA,
			      double *matrixB,
			      const int& matrix_dimension,
			      const int& trials)
{
  // warm-up
  auto start = chrono::high_resolution_clock::now();
  
  for (int iblock = 0; iblock < matrix_dimension; iblock+=blocksize) {
    for (int jblock = 0; jblock < matrix_dimension; jblock+=blocksize) {    
    
      for(int i=iblock;i<min(iblock+blocksize,matrix_dimension);i++){    
	for(int j=jblock;j<min(jblock+blocksize,matrix_dimension);j++){
	  // jth iteration of matrix A has spatial locality
	  // jth iteration of matrix B has to load each column into cache every write
	  matrixB[idx(i,j)] = matrixA[idx(j,i)];
	}    
      }
      
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

    for (int iblock = 0; iblock < matrix_dimension; iblock+=blocksize) {
      for (int jblock = 0; jblock < matrix_dimension; jblock+=blocksize) {    
    
	for(int i=iblock;i<min(iblock+blocksize,matrix_dimension);i++){    
	  for(int j=jblock;j<min(jblock+blocksize,matrix_dimension);j++){
	    // jth iteration of matrix A has spatial locality
	    // jth iteration of matrix B has to load each column into cache every write
	    matrixB[idx(i,j)] = matrixA[idx(j,i)];
	  }    
	}
      
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

}


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
