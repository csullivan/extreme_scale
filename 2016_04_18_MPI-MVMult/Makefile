CC=cc
CFLAGS= -O2 -craympich-mt


EXEC=mmvmpi
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
