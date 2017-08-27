#include <omp.h>
#include <stdio.h>
void main()
{
int i,myval;
#pragma omp parallel for private(myval) ordered
   for(i=1; i<=10; i++)
     {
      myval = i+2;
      #pragma omp ordered
          printf("%d %d\n", i, myval);
     }
}