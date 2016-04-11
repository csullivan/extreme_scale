echo "################ Blocking: ##################"
for i in `seq 2 18`;
do
    echo "Message size: "$((2**i))" bytes"
    echo ""
    mpiexec -n 2 ./bin/pt2pt_blocking $(((2**i)/4))
done

#mpiexec -n 2 ./bin/pt2pt_nonblocking 400000
#mpiexec -n 2 ./bin/pt2pt_nonblocking_head2head 400000
