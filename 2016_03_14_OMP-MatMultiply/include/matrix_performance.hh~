#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>

/* Column-major order (Same as Fortran). 
   This means consecutive elements in a column are 
   stored in contiguous memory. */
#define idx(a,b) ((b)*matrix_dimension+a)
#define STREAM_COPY (41539100000)
#define ppMIN(a,b) \
  ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })


using namespace std;


inline double* basic_matrix_multiply(const double* matrixA, double *matrixB, const int& matrix_dimension, const int& trials) {

  // allocate result matrix (C = A*B)
  auto matrixC = (double*)calloc(matrix_dimension*matrix_dimension,sizeof(double));
  
    // warm-up
  auto start = chrono::high_resolution_clock::now();  
  for(int i=0;i<matrix_dimension;i++){
    for(int j=0;j<matrix_dimension;j++){
      double sum = 0.;
      for(int k=0;k<matrix_dimension;k++){
	sum += matrixA[idx(i,k)]*matrixB[idx(k,j)];
      }
      matrixC[idx(i,j)]=sum;
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
	double sum = 0.;
	for(int k=0;k<matrix_dimension;k++){
	  sum += matrixA[idx(i,k)]*matrixB[idx(k,j)];
	}
	matrixC[idx(i,j)]=sum;
      }
    }
    stop = chrono::high_resolution_clock::now();
    tperformance +=
      chrono::duration_cast<chrono::microseconds>(stop - start).count();
  }

  // ----------------------------------------------------------------------
  
  tperformance = tperformance*1e-6/trials;
  cout << "Matrix dim (n), Basic M. M. (s), Prediction (Assumption 1), Prediction (Assumption 2):   ";
  cout << setw(7) << matrix_dimension <<" "<< scientific << setprecision(3);
  cout  << tperformance << " ";  
  double rw = 1e-9; // sec / double precision word
  double c = 0.2e-9; // sec / floating pt operation
  double n = matrix_dimension;
  double t_model1 = 8*c*n*n*n + (2*rw+rw)*n*n;
  double t_model2 = (8*c+rw)*n*n*n + (rw+rw)*n*n;
  cout << t_model1 << " " << t_model2 << " ";
  cout << endl;

  return matrixC;
  

}
inline double* blocked_matrix_multiply(const int& blocksize,
				       const double* matrixA,
				       const double *matrixB,
				       const int& matrix_dimension,
				       const int& trials)
{
  // allocate result matrix (C = A*B)
  auto matrixC = (double*)calloc(matrix_dimension*matrix_dimension,sizeof(double));
  double sum; // element sum
  // warm-up
  
  auto start = chrono::high_resolution_clock::now();

  for(int jblock=0;jblock<matrix_dimension;jblock+= blocksize){
    for(int kblock=0;kblock<matrix_dimension;kblock+= blocksize){

      for(int i=0;i<matrix_dimension;i++){
	for(int j = jblock; j<((jblock+blocksize)>matrix_dimension?matrix_dimension:(jblock+blocksize)); j++){

	  sum = 0;
	  for(int k = kblock; k<((kblock+blocksize)>matrix_dimension?matrix_dimension:(kblock+blocksize)); k++){
	    sum += matrixA[idx(i,k)]*matrixB[idx(k,j)];
	  }

	  matrixC[idx(i,j)] = sum;
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

  //Broken///////
  //   for (int iblock = 0; iblock < matrix_dimension; iblock+=blocksize) {
  //     for (int jblock = 0; jblock < matrix_dimension; jblock+=blocksize) {    
    
  // 	for(int i=iblock;i<ppMIN(iblock+blocksize,matrix_dimension);i++){    
  // 	  for(int j=jblock;j<ppMIN(jblock+blocksize,matrix_dimension);j++){

  // 	    double sum = 0.;
  // 	    for(int k=0;k<matrix_dimension;k++){
  // 	      sum += matrixA[idx(i,k)]*matrixB[idx(k,j)];
  // 	    }
  // 	    matrixC[idx(i,j)]=sum;
	    
  // 	  }    
  // 	}
      
  //     }
  //   }

    for(int jblock=0;jblock<matrix_dimension;jblock+= blocksize){
      for(int kblock=0;kblock<matrix_dimension;kblock+= blocksize){
      
	for(int i=0;i<matrix_dimension;i++){
	  for(int j = jblock; j<((jblock+blocksize)>matrix_dimension?matrix_dimension:(jblock+blocksize)); j++){
	  
	    sum = 0;
	    for(int k = kblock; k<((kblock+blocksize)>matrix_dimension?matrix_dimension:(kblock+blocksize)); k++){
	      sum += matrixA[idx(i,k)]*matrixB[idx(k,j)];
	    }

	    matrixC[idx(i,j)] = sum;
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
  cout << "Matrix dim (n), Blocked M. M. (s), Prediction (Assumption 1), Prediction (Assumption 2): ";
  cout << setw(7) << matrix_dimension <<" "<< scientific << setprecision(3);
  cout  << tperformance << " ";
  double rw = 1e-9; // sec / double precision word
  double c = 0.2e-9; // sec / floating pt operation
  double n = matrix_dimension;
  double t_model1 = 8*c*n*n*n + (2*rw+rw)*n*n;
  double t_model2 = (8*c+rw)*n*n*n + (rw+rw)*n*n;
  cout << t_model1 << " " << t_model2 << " ";
  cout << endl;

  return matrixC;
}

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
  int L = 8; // assuppMINg cacheline holds 64 bytes 8 = 64 / sizeof(dble)
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
    
      for(int i=iblock;i<ppMIN(iblock+blocksize,matrix_dimension);i++){    
	for(int j=jblock;j<ppMIN(jblock+blocksize,matrix_dimension);j++){
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
    
	for(int i=iblock;i<ppMIN(iblock+blocksize,matrix_dimension);i++){    
	  for(int j=jblock;j<ppMIN(jblock+blocksize,matrix_dimension);j++){
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
  int L = 8; // assuppMINg cacheline holds 64 bytes 8 = 64 / sizeof(dble)
  cout  << matrix_dimension*matrix_dimension*(rwtime+L*rwtime) << " ";
  cout<< endl;

}


void check_transpose(const double* matrix, const int& matrix_dimension);
void print_matrix(const double* matrix, size_t matrix_dimension);
