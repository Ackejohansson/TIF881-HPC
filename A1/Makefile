# Makefile for compiling C code with different optimization levels

# Compiler
CC = gcc

# Compiler flags
CFLAGS_INLINE = -O2 -march=native

# Output directory for generated files
OUTPUT_DIR = output
ASM_DIR = $(OUTPUT_DIR)/asm
EXE_DIR = $(OUTPUT_DIR)/exe

# Default target: compile all optimization levels and all source files
all: $(EXE_DIR)/samef $(EXE_DIR)/difff

# Create output directories
$(OUTPUT_DIR) $(ASM_DIR) $(EXE_DIR):
	@mkdir -p $@

$(EXE_DIR)/samef: $(OUTPUT_DIR) samefile.c | $(EXE_DIR)
	$(CC) $(CFLAGS_INLINE) -o $@ $<

$(EXE_DIR)/difff: $(OUTPUT_DIR) different_file.c mul_cpx.c | $(EXE_DIR)
	$(CC) $(CFLAGS_INLINE) -o $@ $^

# Clean generated files
clean:
	@rm -rf $(OUTPUT_DIR)

.PHONY: all clean
