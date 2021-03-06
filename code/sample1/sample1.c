/**
  Sample OpenMP program printing hello world with
  their respective thread ID.
*/
#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char const *argv[]) {

  #pragma omp parallel
  {
      int ID = omp_get_thread_num();
      printf("Hello(%d) ",ID );
      printf("World(%d)\n",ID );
  }
  return 0;

}
