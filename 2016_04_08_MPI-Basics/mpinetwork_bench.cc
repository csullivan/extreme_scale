#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cmath>

#include "mpipingpong.hh"

using namespace std;

void SignalHandler(int s) {
  int size; MPI_Comm_size(MPI_COMM_WORLD, &size);
  cout << "Caught signal: "<< s << ". Shutting down.." << endl;
  if (size > 1) {
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
  }
  exit(1);
}

int main(int argc, char** argv) {

  // install the interupt handler, to prevent an MPI hay day
  // ie let's not fork up the cluster
  struct sigaction InteruptHandler;
  InteruptHandler.sa_handler = SignalHandler;
  sigemptyset(&InteruptHandler.sa_mask);
  InteruptHandler.sa_flags = 0;
  sigaction(SIGINT, &InteruptHandler, NULL);

  MPI_Init(&argc, &argv);

  int32_t rank; MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int32_t wsize; MPI_Comm_size(MPI_COMM_WORLD, &wsize);


  uint32_t mcount = 0;
  if (argc > 1) {
    mcount = atoi(argv[1]);
    mpi_network_bench(0,1,mcount,10);
  } else {

    if (rank==0) cout << "\n###################### rank_i = 0  -  rank_j = 1 ######################" << endl;
    for (int32_t i=2; i<=18; i++) {
      mcount = (pow(2,i)/4);
      if (rank==0) cout << "### Message size (bytes): " << mcount*4 << " ###\n";
      mpi_network_bench(0,1,mcount,10);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank==0) cout << "\n###################### rank_i = 0  -  rank_j = wsize-1 ######################" << endl;
    for (int32_t i=2; i<=18; i++) {
      mcount = (pow(2,i)/4);
      if (rank==0) cout << "### Message size (bytes): " << mcount*4 << " ###\n";
      mpi_network_bench(0,wsize-1,mcount,10);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    int even = 16;
    if (wsize>=even+1) {
      if (rank==even) cout << "\n###################### rank_i = 16  -  rank_j = 17 ######################" << endl;
      for (int32_t i=2; i<=18; i++) {
        mcount = (pow(2,i)/4);
        if (rank==even) cout << "### Message size (bytes): " << mcount*4 << " ###\n";
        mpi_network_bench(even,even+1,mcount,10);
      }
    }

  }

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();

  return 0;
}
