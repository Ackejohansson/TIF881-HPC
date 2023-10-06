CC = gcc
CFLAGS_INLINE = -O2 -lm -march=native

all: newton

newton: newton.c
	$(CC) $(CFLAGS_INLINE) -o $@ $<

clean:
	rm -f newton

.PHONY: all clean