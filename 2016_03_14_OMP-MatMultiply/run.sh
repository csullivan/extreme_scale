export OMP_NUM_THREADS=1
echo "OMP_NUM_THREADS="$OMP_NUM_THREADS
./bin/matrix-matrix-multiply 20
./bin/matrix-matrix-multiply 100
./bin/matrix-matrix-multiply 1000
./bin/matrix-matrix-multiply 1700
export OMP_NUM_THREADS=2
echo "OMP_NUM_THREADS="$OMP_NUM_THREADS
./bin/matrix-matrix-multiply 20
./bin/matrix-matrix-multiply 100
./bin/matrix-matrix-multiply 1000
./bin/matrix-matrix-multiply 1700
export OMP_NUM_THREADS=4
echo "OMP_NUM_THREADS="$OMP_NUM_THREADS
./bin/matrix-matrix-multiply 20
./bin/matrix-matrix-multiply 100
./bin/matrix-matrix-multiply 1000
./bin/matrix-matrix-multiply 1700
export OMP_NUM_THREADS=8
echo "OMP_NUM_THREADS="$OMP_NUM_THREADS
./bin/matrix-matrix-multiply 20
./bin/matrix-matrix-multiply 100
./bin/matrix-matrix-multiply 1000
./bin/matrix-matrix-multiply 1700
export OMP_NUM_THREADS=16
echo "OMP_NUM_THREADS="$OMP_NUM_THREADS
./bin/matrix-matrix-multiply 20
./bin/matrix-matrix-multiply 100
./bin/matrix-matrix-multiply 1000
./bin/matrix-matrix-multiply 1700
export OMP_NUM_THREADS=32
echo "OMP_NUM_THREADS="$OMP_NUM_THREADS
./bin/matrix-matrix-multiply 20
./bin/matrix-matrix-multiply 100
./bin/matrix-matrix-multiply 1000
./bin/matrix-matrix-multiply 1700
