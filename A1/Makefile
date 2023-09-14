# Makefile for compiling C code with different optimization levels

# Compiler
CC = gcc

# Output directory for generated files
OUTPUT_DIR = output
ASM_DIR = $(OUTPUT_DIR)/asm
EXE_DIR = $(OUTPUT_DIR)/exe

# Optimization levels
OPTIMIZATION_LEVELS = -O0 -O1 -O2 -O3

# Default target: compile all optimization levels and all source files
all: samefile


# Create output directories
$(OUTPUT_DIR) $(ASM_DIR) $(EXE_DIR):
	@mkdir -p $@

samefile: samefile.c
	gcc -o $@ $< -O2 -march=native

# Clean generated files
clean:
	@rm -rf $(OUTPUT_DIR)

.PHONY: all clean

# USe @ for target name and < for first dependency