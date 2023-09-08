# Makefile for compiling C code with different optimization levels

# Compiler
CC = gcc

# Source file
SOURCE = sumofbillion.c

# Output directory for assembly files
ASM_DIR = asm

# Optimization levels
OPTIMIZATION_LEVELS = -O0 -O1 -O2 -O3

# Default target: compile all optimization levels
all: $(OPTIMIZATION_LEVELS)

# Compile with different optimization levels
$(OPTIMIZATION_LEVELS):
	@echo "Compiling with optimization level $@"
	@mkdir -p $(ASM_DIR)
	@$(CC) -S $(SOURCE) -o $(ASM_DIR)/$@.s $@

# Clean generated files
clean:
	@rm -rf $(ASM_DIR)

.PHONY: all clean
