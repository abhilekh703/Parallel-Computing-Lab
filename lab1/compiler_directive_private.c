#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int nthreads, tid;
int i=5;

/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nthreads, tid) private(i)
  {

  /* Obtain thread number */
  tid = omp_get_thread_num();
  printf("Hello World from thread = %d, i=%d\n", tid,i);
   i=i++;
printf("Hello World from thread = %d, i=%d after incr of i\n", tid,i);
  /* Only master thread does this */
  if (tid == 0) 
    {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }

  }  /* All threads join master thread and disband */

}