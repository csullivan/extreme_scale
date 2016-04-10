#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "mpi.h"

#include "Timer.hh"

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

  int wsize; MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  int rank; MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  uint32_t mcount = 0; // message size in bytes

  // allocate the memory
  if (argc > 1) mcount = atoi(argv[1]);
  auto sendbuffer = new float[mcount]();
  auto recbuffer = new float[mcount]();
  int ntrials = 10;
  double start = 0, end = 0, elapsed = 0;
  double tperformance = 2112112.0;

  if (rank == 0) cout << "\nBlocking:\n";
  for (int i=0; i<ntrials; i++)
  {
    // initialize
    for (uint32_t i=0;i<mcount;i++){
      if (rank ==0) sendbuffer[i] = 9999;
      if (rank ==1) sendbuffer[i] = 2112;
    }

    start = MPI_Wtime();
    if (rank == 0) {
      MPI_Send(sendbuffer, mcount, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
      MPI_Recv(recbuffer, mcount, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    if (rank == 1) {
      MPI_Recv(recbuffer, mcount, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Send(sendbuffer, mcount, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
    }
    end = MPI_Wtime();
    elapsed = (end - start);
    if (elapsed<tperformance) tperformance = elapsed;

  }
  if ((rank==0 && recbuffer[mcount-1]==2112) || (rank==1 && recbuffer[mcount-1]==9999)) cout << "mpiwall: Rank "<<rank<<" - Minimum time: " << tperformance*1e3 << " ms\n";


  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();

  return 0;
}
