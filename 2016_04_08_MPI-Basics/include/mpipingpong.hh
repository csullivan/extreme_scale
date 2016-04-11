#include <iostream>
#include <functional>

#include "mpi.h"

using namespace std;

void blocking_comm(const int32_t& rank, const int32_t& rank_i, const int32_t& rank_j, const uint32_t& mcount, float* sendbuffer, float* recbuffer) {
  if (rank == rank_i) {
    MPI_Send(sendbuffer, mcount, MPI_FLOAT, rank_j, 0, MPI_COMM_WORLD);
    MPI_Recv(recbuffer, mcount, MPI_FLOAT, rank_j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  if (rank == rank_j) {
    MPI_Recv(recbuffer, mcount, MPI_FLOAT, rank_i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(sendbuffer, mcount, MPI_FLOAT, rank_i, 0, MPI_COMM_WORLD);
  }
}
void nonblocking_comm(const int32_t& rank, const int32_t& rank_i, const int32_t& rank_j, const uint32_t& mcount, float* sendbuffer, float* recbuffer) {
  MPI_Status stat[4];
  MPI_Request req[4];
  if (rank == rank_i) {
    MPI_Isend(sendbuffer, mcount, MPI_FLOAT, rank_j, 0, MPI_COMM_WORLD, &req[1]); // rank 0 post send to rank 1
    MPI_Irecv(recbuffer, mcount, MPI_FLOAT, rank_j, 0, MPI_COMM_WORLD, &req[2]); // rank 0 post recieve from rank 1
    MPI_Wait(&req[1],&stat[1]);
    MPI_Wait(&req[2],&stat[2]);
  }
  if (rank == rank_j) {
    MPI_Irecv(recbuffer, mcount, MPI_FLOAT, rank_i, 0, MPI_COMM_WORLD, &req[0]); // rank 1 post recieve from rank 0
    MPI_Isend(sendbuffer, mcount, MPI_FLOAT, rank_i, 0, MPI_COMM_WORLD, &req[3]); // rank 1 post send to rank 0
    MPI_Wait(&req[0],&stat[0]);
    MPI_Wait(&req[3],&stat[3]);
  }
}
void headtohead_comm(const int32_t& rank, const int32_t& rank_i, const int32_t& rank_j, const uint32_t& mcount, float* sendbuffer, float* recbuffer) {

  if (rank == rank_i || rank == rank_j) {
    MPI_Request req[2];
    const int32_t partner_rank = (rank == rank_i) ? rank_j : rank_i;
    MPI_Irecv(recbuffer, mcount, MPI_FLOAT, partner_rank, 0, MPI_COMM_WORLD, &req[0]);
    MPI_Isend(sendbuffer, mcount, MPI_FLOAT, partner_rank, 0, MPI_COMM_WORLD, &req[1]);
    MPI_Waitall(2,req,MPI_STATUS_IGNORE);
  }
}
void mpi_network_bench(int32_t rank_i, int32_t rank_j, uint32_t mcount, uint32_t ntrials=5) {

  int32_t rank; MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  float* sendbuffer = new float[mcount]();
  float* recbuffer = new float[mcount]();
  double start = 0, end = 0, elapsed = 0, tperformance = 1e8;

  auto benchmark = [&](
    function<void(const int32_t&,
                  const int32_t&,
                  const int32_t&,
                  const uint32_t&,
                  float*, float*)> callable)
    {
      for (uint32_t i=0; i<ntrials; i++)
      {
        // initialize
        for (uint32_t i=0;i<mcount;i++){
          if (rank == rank_i) sendbuffer[i] = rank_i;
          if (rank == rank_j) sendbuffer[i] = rank_j;
        }
        start = MPI_Wtime(); // start the timer
        callable(rank,rank_i,rank_j,mcount,sendbuffer,recbuffer);
        end = MPI_Wtime(); // stop the timer
        elapsed = (end - start);
        if (elapsed<tperformance) tperformance = elapsed;
      }
      if ((rank==rank_i && recbuffer[mcount-1]==rank_j) || (rank==rank_j && recbuffer[mcount-1]==rank_i)) {
        if (rank==0) cout << "Rank "<<rank<<" - Minimum time: " << tperformance*1e3 << " ms\n";
      }
  };

  // benchmarks
  if (rank == 0) cout << "    Blocking ";
  benchmark(blocking_comm); start = 0, end = 0, elapsed = 0, tperformance = 1e8;
  if (rank == 0) cout << "Non-blocking ";
  benchmark(nonblocking_comm); start = 0, end = 0, elapsed = 0, tperformance = 1e8;
  if (rank == 0) cout << "Head-to-head ";
  benchmark(headtohead_comm); start = 0, end = 0, elapsed = 0, tperformance = 1e8;

}
