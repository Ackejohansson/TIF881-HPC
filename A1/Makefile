# Compiler
CC = gcc

# Compiler flags
CFLAGS_INLINE = -O2 -march=native

# Output directory for generated executables
EXE_DIR = exe

# Source files
SAMEFILE_SRC = same_file.c
DIFFERENTFILE_SRC = different_file.c mul_cpx.c

# Executable names
SAMEF = samef
DIFFF = difff

# Default target: compile both executables
all: $(EXE_DIR)/$(SAMEF) $(EXE_DIR)/$(DIFFF)

# Create the 'exe' directory if it doesn't exist
$(EXE_DIR):
	@mkdir -p $@

$(EXE_DIR)/$(SAMEF): $(EXE_DIR) $(SAMEFILE_SRC)
	$(CC) $(CFLAGS_INLINE) -o $@ $(SAMEFILE_SRC)

$(EXE_DIR)/$(DIFFF): $(EXE_DIR) $(DIFFERENTFILE_SRC)
	$(CC) $(CFLAGS_INLINE) -o $@ $(DIFFERENTFILE_SRC)

# Clean generated executables
clean:
	@rm -rf $(EXE_DIR)

.PHONY: all clean
