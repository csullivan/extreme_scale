ALL: all-redirect

# Change these to match your compilers
CC = gcc
FC = gfortran
# Make sure you use optimization - it can make a big business
CFLAGS = -O2
FCFLAGS = -O2

EXECS = mm mmc

all-redirect: $(EXECS)

mm: mm.o dummyf.o mysecond.o
	$(FC) -o mm $(FCFLAGS) mm.o dummyf.o mysecond.o

mmc: mmc.o dummy.o mysecond.o
	$(CC) -o mmc $(CFLAGS) mmc.o dummy.o mysecond.o

.c.o:
	$(CC) -c $(CFLAGS) $<
.f.o:
	$(FC) -c $(FCFLAGS) $<

clean:
	rm -f *.o

realclean: clean
	rm -f $(EXECS)

.PHONY: clean realclean all-redirect
