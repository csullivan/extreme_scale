CC=cc
CFLAGS= -O3 -craympich-mt
ifndef _CRAYC
CC=mpicc
CFLAGS= -O3
endif


EXEC=ioda
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
ASSEMBS = $(SOURCES:.c=.s)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

%.s: %.c
	$(CC) $(CFLAGS) -S $^

assemb: $(ASSEMBS)

.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJECTS) $(ASSEMBS)
	rm -f *~
