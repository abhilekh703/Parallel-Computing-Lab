#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omp.h"

#define MAX_SIZE 100000

void merge(int * X, int n, int * tmp) 
{
   int i = 0;
   int j = n/2;
   int ti = 0;

   while (i<n/2 && j<n) 
   {
      if (X[i] < X[j]) 
      {
         tmp[ti] = X[i];
         ti++; i++;
      } 
      else 
      {
         tmp[ti] = X[j];
         ti++; j++;
      }
   }
   while (i<n/2) 
   {
      tmp[ti] = X[i];
      ti++; i++;
   }
  while (j<n) 
  {
         tmp[ti] = X[j];
         ti++; j++;
   }
   memcpy(X, tmp, n*sizeof(int));

}

void mergesort(int * X, int n, int * tmp)
{
   if (n < 2) return;

   #pragma omp task firstprivate (X, n, tmp)
{
	printf("thread id task 1: %d \n",omp_get_thread_num());
   mergesort(X, n/2, tmp);
}

   #pragma omp task firstprivate (X, n, tmp)
   {
	printf("thread id task2: %d \n",omp_get_thread_num());
	mergesort(X+(n/2), n-(n/2), tmp);
}	 
   #pragma omp taskwait
   
   merge(X, n, tmp);
}


int main()
{
   int n,i,th;
   double start, stop;
   printf("enter the size of array\n");
   scanf("%d",&n);
   int data[MAX_SIZE], tmp[MAX_SIZE];

  for(i=0;i<n;i++)
  {
     data[i] = rand() % n;
   }
   
   printf("enter the number of threads\n");
   scanf("%d",&th);
   start = omp_get_wtime();
   #pragma omp parallel num_threads(th)
   {
      #pragma omp single
    {
	printf("thread id : %d\n ",omp_get_thread_num());
      mergesort(data, n, tmp);
      printf("Number of threads are %d",omp_get_num_threads());
    }
   }
   stop = omp_get_wtime();
   printf("\nTime: %g\n",stop-start);
}

