/**
  Headerfile related to the definition of convenient data types used within the
  matrix multiplication program.
*/

#ifndef __CONVENIENT_DATA_TYPES_H__
#define __CONVENIENT_DATA_TYPES_H__

#include<ctype.h>

typedef int Matrix;
typedef int mat_row;
typedef int mat_col;


typedef struct mat_dim {
  mat_row row;
  mat_col col;
}mat_dim;


#endif
