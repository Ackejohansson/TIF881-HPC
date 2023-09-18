# Compiler
CC = gcc
CFLAGS_INLINE = -O2 -march=native
EXE_DIR = exe

all: $(EXE_DIR)/samef $(EXE_DIR)/difff

# Create the 'exe' directory if it doesn't exist
$(EXE_DIR):
	@mkdir -p $@


samef: $(EXE_DIR)/samef
$(EXE_DIR)/samef: $(EXE_DIR) same_file.c
	$(CC) $(CFLAGS_INLINE) -o $@ same_file.c

difff: $(EXE_DIR)/difff
$(EXE_DIR)/difff: $(EXE_DIR) different_file.c mul_cpx.c
	$(CC) $(CFLAGS_INLINE) -o $@ different_file.c mul_cpx.c

locality: $(EXE_DIR)/locality
$(EXE_DIR)/locality: $(EXE_DIR) locality.c
	$(CC) -O0 -o $@_O0 locality.c
	$(CC) -O2 -o $@_O2 locality.c

clean:
	@rm -rf $(EXE_DIR)

.PHONY: all clean
