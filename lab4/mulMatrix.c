#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int m1,n2,m2,n1;
	printf("enter the no of rows and columns of mat1 and mat2: ");
	scanf("%d%d%d%d",&m1,&n1,&m2,&n2);
	if(n1!=m2)
		printf("cannot multiply\n");
	else
	{
		int a[m1][n1], b[m2][n2], c[m1][n2];
		int i,j,k;
		printf("Enter mat 1: ");
		for(i=0;i<m1;i++)
			for(j=0;j<n1;j++)
				scanf("%d",&a[i][j]);
		printf("Entr matrix 2: ");
		for(i=0;i<m2;i++)
			for(j=0;j<n2;j++)
				scanf("%d",&b[i][j]);

		for(i=0;i<m2;i++)
			for(j=0;j<n2;j++)
				c[i][j]=0;

		int chunk,nthreads;
		printf("Enter the chunksize and no of threads: ");
		scanf("%d%d",&chunk,&nthreads);

		#pragma omp parallel shared(a,b,c,m1,m2,n1,n2) private(i,j,k) num_threads(nthreads)
		#pragma omp for collapse(3) schedule(static,chunk) ordered
		for(i=0;i<m1;i++)
			for(j=0;j<n2;j++)
				for(k=0;k<n1;k++)
					c[i][j] += a[i][k]*b[k][j];

		printf("Multiplied Matrix\n");
		for(i=0;i<m1;i++)
		{
			for(j=0;j<n2;j++)
				printf("%d\t",c[i][j]);
			printf("\n");
		}

	}

	return 0;
}