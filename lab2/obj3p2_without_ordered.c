#include <omp.h>
#include <stdio.h>
void main()
{
int i,myval;
#pragma omp parallel for private(myval)
   for(i=1; i<=10; i++)
     {
      myval = i+2;
          printf("%d %d\n", i, myval);
     }
}
