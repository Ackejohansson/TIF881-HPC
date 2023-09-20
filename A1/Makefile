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
	$(CC) -O0 -march=native -o $@_O0 locality.c
	$(CC) -O2 -march=native -o $@_O2 locality.c

datadeps: $(EXE_DIR)/datadeps
$(EXE_DIR)/datadeps: $(EXE_DIR) data_deps.c
	$(CC) -O0 -march=native -o $@_O0 data_deps.c
	$(CC) -O2 -march=native -o $@_O2 data_deps.c

indirect: $(EXE_DIR)/indirect
$(EXE_DIR)/indirect: $(EXE_DIR) indirect_addressing.c
	$(CC) -O0 -march=native -o $@_O0 indirect_addressing.c
	$(CC) -O2 -march=native -o $@_O2 indirect_addressing.c

clean:
	@rm -rf $(EXE_DIR)

.PHONY: all clean
