# Makefile for compiling C code with different optimization levels

# Compiler
CC = gcc

# Source file
SOURCE = sumofbillion.c
SAME_FILE_SOURCE = same_file.c
DIFFERENT_FILE_MUL_SOURCE = different_file_mul.c
VALGRIND_SOURCE = valgrind.c

# Output directory for generated files
OUTPUT_DIR = output

# Output directory for assembly files
ASM_DIR = $(OUTPUT_DIR)/asm

# Output directory for executable files
EXE_DIR = $(OUTPUT_DIR)/exe

# Optimization levels
OPTIMIZATION_LEVELS = -O0 -O1 -O2 -O3

# Executable names
SUMOFBILLION_EXEC = sumofbillion
SAME_FILE_EXEC = same_file
DIFFERENT_FILE_MUL_EXEC = different_file_mul
VALGRIND_EXEC = valgrind

# Default target: compile all optimization levels and all source files
all: $(OPTIMIZATION_LEVELS) $(SUMOFBILLION_EXEC) $(SAME_FILE_EXEC) $(DIFFERENT_FILE_MUL_EXEC) $(VALGRIND_EXEC)

# Create output directories
$(OUTPUT_DIR) $(ASM_DIR) $(EXE_DIR):
	@mkdir -p $@

# Compile with different optimization levels
$(OPTIMIZATION_LEVELS): | $(ASM_DIR) $(EXE_DIR)
	@echo "Compiling with optimization level $@"
	@$(CC) -S $(SOURCE) -o $(ASM_DIR)/$@.s $@
	@$(CC) $(ASM_DIR)/$@.s -o $(EXE_DIR)/$@-$(SUMOFBILLION_EXEC)

# Compile same_file.c
$(SAME_FILE_EXEC): | $(EXE_DIR)
	@echo "Compiling $@"
	@$(CC) $(SAME_FILE_SOURCE) -o $(EXE_DIR)/$@

# Compile different_file_mul.c
$(DIFFERENT_FILE_MUL_EXEC): | $(ASM_DIR) $(EXE_DIR)
	@echo "Compiling $@"
	@$(CC) -S $(DIFFERENT_FILE_MUL_SOURCE) -o $(ASM_DIR)/$@.s
	@$(CC) $(ASM_DIR)/$@.s -o $(EXE_DIR)/$@

# Compile valgrind.c
$(VALGRIND_EXEC): | $(EXE_DIR)
	@echo "Compiling $@"
	@$(CC) $(VALGRIND_SOURCE) -o $(EXE_DIR)/$@

# Clean generated files
clean:
	@rm -rf $(OUTPUT_DIR)

.PHONY: all clean
