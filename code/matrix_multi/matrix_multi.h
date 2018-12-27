#ifndef __MATRIX_MULTI_H__
#define __MATRIX_MULTI_H__


#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "convenient_data_types.h"
#include "convenience_methods.h"


/**Function Prototypes*/

int pseudoRandomNumberGenWithinLimit(int p_limit);


RETVALS_FUNCS allocateMatrices(Matrix ***A, Matrix ***B, Matrix ***Res_Serial, Matrix ***Res_OpenMP, mat_dim *a_dim, mat_dim *b_dim);
RETVALS_FUNCS deallocateMatrices(Matrix ***A, Matrix ***B, Matrix ***Res_Serial, Matrix ***Res_OpenMP, mat_dim *a_dim, mat_dim *b_dim);


RETVALS_FUNCS loadMatrixSizes(mat_dim *a_dim, mat_dim *b_dim);
RETVALS_FUNCS loadValuesToMatrices(Matrix ***A, Matrix ***B, mat_dim *a_dim, mat_dim *b_dim);

RETVALS_FUNCS MatrixMultiplySerial(Matrix ***A, Matrix ***B, Matrix ***Res_Serial, mat_dim *a_dim, mat_dim *b_dim);
RETVALS_FUNCS MatrixMultiplyWithOpenMP(Matrix ***A, Matrix ***B, Matrix ***Res_OpenMP, mat_dim *a_dim, mat_dim *b_dim);

RETVALS_FUNCS MatricesAreEqual(Matrix ***Res_Serial, Matrix ***Res_OpenMP, mat_dim *res_dim);

#endif
