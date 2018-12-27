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

RETVALS_FUNCS allocateMatrices(Matrix ***A, Matrix ***B, Matrix ***Res_Serial, Matrix ***Res_OpenMP, mat_dim *a_dim, mat_dim *b_dim) {

  int row_idx, col_idx;

  *A = (Matrix**) malloc(sizeof(Matrix*) * a_dim->row);
  *B = (Matrix**) malloc(sizeof(Matrix*) * b_dim->row);
  *Res_Serial = (Matrix**) malloc(sizeof(Matrix*) * a_dim->row);
  *Res_OpenMP = (Matrix**) malloc(sizeof(Matrix*) * a_dim->row);


  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
      (*A)[row_idx] = (Matrix*) malloc(sizeof(Matrix) * a_dim->col);
  }

  for(row_idx=0;row_idx < b_dim->row; row_idx++) {
      (*B)[row_idx] = (Matrix*) malloc(sizeof(Matrix) * b_dim->col);
  }

  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
      (*Res_Serial)[row_idx] = (Matrix*) malloc(sizeof(Matrix) * b_dim->col);
  }

  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
      (*Res_OpenMP)[row_idx] = (Matrix*) malloc(sizeof(Matrix) * b_dim->col);
  }
  return RETVALS_FUNCS_SUCCESS;
}
RETVALS_FUNCS deallocateMatrices(Matrix ***A, Matrix ***B, Matrix ***Res_Serial, Matrix ***Res_OpenMP, mat_dim *a_dim, mat_dim *b_dim) {

  int row_idx;

  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
      free((*A)[row_idx]);
  }
  for(row_idx=0;row_idx < b_dim->row; row_idx++) {
      free((*B)[row_idx]);
  }
  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
      free((*Res_Serial)[row_idx]);
  }
  for(row_idx=0;row_idx < a_dim->row; row_idx++) {
      free((*Res_OpenMP)[row_idx]);
  }

  free(*A);
  free(*B);
  free(*Res_Serial);
  free(*Res_OpenMP);

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

RETVALS_FUNCS MatrixMultiplySerial(Matrix ***A, Matrix ***B, Matrix ***Res_Serial, mat_dim *a_dim, mat_dim *b_dim) {

  int row_idx, col_idx, pdt_idx, sum;


  for(row_idx=0; row_idx < a_dim->row; row_idx++) {
    for(col_idx=0; col_idx < b_dim->col; col_idx++) {
      for(pdt_idx=0; pdt_idx < b_dim->row; pdt_idx++) {
	       sum = sum + (*A)[row_idx][pdt_idx]*(*B)[pdt_idx][col_idx];
      }
      (*Res_Serial)[row_idx][col_idx] = sum;
      sum = 0;
    }
  }
}


RETVALS_FUNCS MatrixMultiplyWithOpenMP(Matrix ***A, Matrix ***B, Matrix ***Res_OpenMP, mat_dim *a_dim, mat_dim *b_dim) {

  int row_idx, col_idx, pdt_idx, sum;


  for(row_idx=0; row_idx < a_dim->row; row_idx++) {
    for(col_idx=0; col_idx < b_dim->col; col_idx++) {
      for(pdt_idx=0; pdt_idx < b_dim->row; pdt_idx++) {
	       sum = sum + (*A)[row_idx][pdt_idx]*(*B)[pdt_idx][col_idx];
      }
      (*Res_OpenMP)[row_idx][col_idx] = sum;
      sum = 0;
    }
  }
}

RETVALS_FUNCS MatricesAreEqual(Matrix ***Res_Serial, Matrix ***Res_OpenMP, mat_dim *res_dim) {

  int row_idx, col_idx;

  for(row_idx=0;row_idx < res_dim->row; row_idx++) {
    for(col_idx=0;col_idx < res_dim->col; col_idx++) {

      if((*Res_OpenMP)[row_idx][col_idx] != (*Res_OpenMP)[row_idx][col_idx]) {
        return RETVALS_FUNCS_UNEQUAL;
      }
    }
  }
  return RETVALS_FUNCS_EQUAL;
}

int main(int argc, char const *argv[]) {


  Matrix **A, **B, **Res_Serial,**Res_OpenMP;
  mat_dim a_dim, b_dim, res_dim;

  if(loadMatrixSizes(&a_dim, &b_dim)!=RETVALS_FUNCS_SUCCESS) {

    printf("\nError:Matrix size mismatch\n");
    exit(0);
  }

  allocateMatrices(&A, &B, &Res_Serial,&Res_OpenMP, &a_dim, &b_dim);

  loadValuesToMatrices(&A, &B, &a_dim, &b_dim);

  MatrixMultiplySerial(&A, &B, &Res_Serial, &a_dim, &b_dim);

  MatrixMultiplyWithOpenMP(&A, &B, &Res_OpenMP, &a_dim, &b_dim);

  res_dim.row = a_dim.row;
  res_dim.col = b_dim.col;

  if(MatricesAreEqual(&Res_Serial, &Res_OpenMP, &res_dim) == RETVALS_FUNCS_EQUAL) {
    printf("The matrices are equal.\n");
  } else {
    printf("The matrices are unequal.\n");
  }

  deallocateMatrices(&A, &B, &Res_Serial, &Res_OpenMP, &a_dim, &b_dim);
  return 0;
}
