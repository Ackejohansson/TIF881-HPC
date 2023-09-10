# Makefile for compiling C code with different optimization levels

# Compiler
CC = gcc

# Source files
SOURCE = sumofbillion.c
VALGRIND_SOURCE = valgrind.c

# Output directory for assembly files
ASM_DIR = asm

# Optimization levels
OPTIMIZATION_LEVELS = -O0 -O1 -O2 -O3

# Default target: compile all optimization levels
all: $(OPTIMIZATION_LEVELS) valgrind

# Compile with different optimization levels
$(OPTIMIZATION_LEVELS):
	@echo "Compiling with optimization level $@"
	@mkdir -p $(ASM_DIR)
	@$(CC) -S $(SOURCE) -o $(ASM_DIR)/$@.s $@

# Compile valgrind.c
valgrind: $(VALGRIND_SOURCE)
	@echo "Compiling valgrind"
	@$(CC) $(VALGRIND_SOURCE) -o valgrind

# Clean generated files
clean:
	@rm -rf $(ASM_DIR) valgrind

.PHONY: all clean
