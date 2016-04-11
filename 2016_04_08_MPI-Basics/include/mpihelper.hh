#include <iostream>
#include <functional>

#include "mpi.h"

using namespace std;

template <typename T>
void mpicout (T item) {
  int32_t rank; MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank==0) cout << item << endl;
}
