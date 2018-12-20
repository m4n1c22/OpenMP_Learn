#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <ctype.h>


/**Macro Constants*/

#define MAX_VALUE	1000

#define A_ROW_SIZE 	500
#define A_COL_SIZE	400

#define B_ROW_SIZE 	400
#define B_COL_SIZE	500

/**Enumerations*/
typedef enum ERR_MATRIX_PGM{

    ER_DIMENSION_MISMATCH = 100
  
}ERR_MATRIX_PGM;

typedef enum RETVALS_FUNCS {

  RETVALS_FUNCS_SUCCESS = 0,
  RETVALS_FUNCS_MEM_ALLOC_FAILED = 1,
  RETVALS_FUNCS_OUT_OF_BOUNDS = 2

  
} RETVALS_FUNCS;


#endif
