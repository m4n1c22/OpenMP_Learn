/**
  OpenMP program simulating matrix multiplication.
*/
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "convenient_data_types.h"
#include "convenience_methods.h"
#include "matrix_multi.h"


/**Function Defintions*/

int pseudoRandomNumberGenWithinLimit(int p_limit) {

   return rand()%p_limit;
   
}

RETVALS_FUNCS allocateMatrices(Matrix ***A, Matrix ***B, Matrix ***C, mat_dim *a_dim, mat_dim *b_dim) {

  int row_idx, col_idx;
  
  *A = (Matrix**) malloc(sizeof(Matrix*) * a_dim->row);
  *B = (Matrix**) malloc(sizeof(Matrix*) * b_dim->row);
  *C = (Matrix**) malloc(sizeof(Matrix*) * a_dim->row);
  
  
  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
      (*A)[row_idx] = (Matrix*) malloc(sizeof(Matrix) * a_dim->col);
  }
  
  for(row_idx=0;row_idx < b_dim->row; row_idx++) {
      (*B)[row_idx] = (Matrix*) malloc(sizeof(Matrix) * b_dim->col);
  }
  
  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
      (*C)[row_idx] = (Matrix*) malloc(sizeof(Matrix) * b_dim->col);
  }
  
  return RETVALS_FUNCS_SUCCESS;
}
RETVALS_FUNCS deallocateMatrices(Matrix ***A, Matrix ***B, Matrix ***C, mat_dim *a_dim, mat_dim *b_dim) {
 
  int row_idx;
  
  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
      free((*A)[row_idx]);
  }
  for(row_idx=0;row_idx < b_dim->row; row_idx++) {
      free((*B)[row_idx]);
  }
  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
      free((*C)[row_idx]);
  }
  
  free(*A);
  free(*B);
  free(*C);
  
 /* A = NULL;
  B = NULL;
  C = NULL;
  */
  return RETVALS_FUNCS_SUCCESS;
}


RETVALS_FUNCS loadMatrixSizes(mat_dim *a_dim, mat_dim *b_dim) {
  
  a_dim->row = A_ROW_SIZE;
  a_dim->col = A_COL_SIZE;
  //a_dim->col = 11;
  b_dim->row = B_ROW_SIZE;
  b_dim->col = B_COL_SIZE;
  
  
  if(b_dim->row != a_dim->col) {
     return RETVALS_FUNCS_OUT_OF_BOUNDS;
  } 
  return RETVALS_FUNCS_SUCCESS;
}

RETVALS_FUNCS loadValuesToMatrices(Matrix ***A, Matrix ***B, mat_dim *a_dim, mat_dim *b_dim) {
  
  int row_idx, col_idx, rand_val;
  
  /**Loading Matrix A*/
  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
    for(col_idx=0;col_idx < a_dim->col; col_idx++) {
      
      rand_val = pseudoRandomNumberGenWithinLimit(MAX_VALUE);
      (*A)[row_idx][col_idx] = rand_val;
    }
  }
  /**Loading Matrix B*/
  for(row_idx=0;row_idx < b_dim->row; row_idx++) {
    for(col_idx=0;col_idx < b_dim->col; col_idx++) {
      
      rand_val = pseudoRandomNumberGenWithinLimit(MAX_VALUE);
      (*B)[row_idx][col_idx] = rand_val;
    }
  }
  return RETVALS_FUNCS_SUCCESS;
}

RETVALS_FUNCS MatrixMultiply(Matrix ***A, Matrix ***B, Matrix ***C, mat_dim *a_dim, mat_dim *b_dim) {

  int row_idx, col_idx, pdt_idx, sum;
  
  
  for(row_idx=0; row_idx < a_dim->row; row_idx++) {
    for(col_idx=0; col_idx < b_dim->col; col_idx++) {
      for(pdt_idx=0; pdt_idx < b_dim->row; pdt_idx++) {
	sum = sum + (*A)[row_idx][pdt_idx]*(*B)[pdt_idx][col_idx];
      }
      (*C)[row_idx][col_idx] = sum;
      sum = 0;
    }
  }
}


int main(int argc, char const *argv[]) {


  Matrix **A, **B, **C;
  mat_dim a_dim, b_dim;

  if(loadMatrixSizes(&a_dim, &b_dim)!=RETVALS_FUNCS_SUCCESS) {
 
    printf("\nError:Matrix size mismatch\n");
    exit(0);
  }
  
  allocateMatrices(&A, &B, &C, &a_dim, &b_dim);
  
  loadValuesToMatrices(&A, &B, &a_dim, &b_dim);
  
  MatrixMultiply(&A, &B, &C, &a_dim, &b_dim);
  
  deallocateMatrices(&A, &B, &C, &a_dim, &b_dim);
  return 0;
}
