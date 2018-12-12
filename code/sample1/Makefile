# C Compiler to use
CC := gcc
# GCC option for linking openmp libraries during compilation.
OMP_OPT := -fopenmp
OUTPUT_OPT := -o
# Sample programs to be used to understand about OpenMP design.
SAMPLE1_SRC := sample1.c
SAMPLE1_EXE := sample1.out

default: run_matrix_mul

comp_sample1:
	${CC} ${SAMPLE1_SRC} ${OMP_OPT} ${OUTPUT_OPT} ${SAMPLE1_EXE}
run_sample1: comp_sample1
	./${SAMPLE1_EXE}
clean_sample1:
	rm ${SAMPLE1_EXE}

comp_matrix_mul:
	${CC} ${MATRIX_MUL_SRC} ${OMP_OPT} ${OUTPUT_OPT} ${MATRIX_MUL_EXE}
run_matrix_mul: comp_matrix_mul
	./${MATRIX_MUL_EXE}
clean_matrix_mul:
	rm ${MATRIX_MUL_EXE}


.PHONY: clean_matrix_mul clean_sample1
