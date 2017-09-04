#include<stdio.h>
#include<stdlib.h>
#include "omp.h"

int fibo(int);

int main()
{
	int nthreads,tid;
	int n=5;
	#pragma omp parallel num_threads(4) private(tid)
	{
		#pragma omp single
		{
			tid = omp_get_thread_num();
			printf("Hello world from (%d)\n",tid);
			printf("Fib(%d)=%d by %d\n",n,fibo(n),tid);
		}
	}
}

int fibo(int n)
{
	int fnm1,fnm2,fn;
      if ( n == 0 || n == 1 ) return(n);

      else
      {
         #pragma omp task shared(fnm1)
           fnm1 = fibo(n-1);
         #pragma omp task shared(fnm2)
           fnm2 = fibo(n-2);
         #pragma omp taskwait
           fn = fnm1 + fnm2;
           return(fn);
       }
}
