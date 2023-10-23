CC = gcc
CFLAGS_INLINE = -O2 -lm -march=native

all: base algexpr operandtype fpu lucol lurow

base: 0base.c
	$(CC) $(CFLAGS_INLINE) -o $@ $<

algexpr: 1algexpr.c
	$(CC) $(CFLAGS_INLINE) -o $@ $<

operandtype: 2operandtype.c
	$(CC) $(CFLAGS_INLINE) -o $@ $<

fpu: 3fpu.c
	$(CC) $(CFLAGS_INLINE) -o $@ $<

lucol: 41loopunrollcol.c
	$(CC) $(CFLAGS_INLINE) -o $@ $<

lurow: 42loopunrollrow.c
	$(CC) $(CFLAGS_INLINE) -o $@ $<

clean:
	rm -f base
	rm -f algexpr
	rm -f operandtype
	rm -f fpu
	rm -f lucol
	rm -f lurow
	
.PHONY: all clean