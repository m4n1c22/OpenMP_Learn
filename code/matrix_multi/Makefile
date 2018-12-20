# C Compiler to use
CC := gcc

# GCC option for linking openmp libraries during compilation.
OMP_OPT := -fopenmp
OUTPUT_OPT := -o

WARN_OPT := -Wall

SOURCE = $(wildcard *.c)
EXE = $(SOURCE:.c=.out)

run: $(EXE)
	./$(EXE)

$(EXE): $(SOURCE)
	$(CC) $(OUTPUT_OPT) $@ $^ $(OMP_OPT)

.PHONY: clean
clean:
	rm -f  $(EXE)

