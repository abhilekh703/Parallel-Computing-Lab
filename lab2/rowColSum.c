#include<stdio.h>
#include<omp.h>

int main()
{
	int N,i,j,chunk,nthreads;
	printf("Enter the no of rows and columns: ");
	scanf("%d",&N);
	int a[N][N], rowSum[N],colSum[N];
	printf("Enter the matrix: ");
	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
			scanf("%d",&a[i][j]);
	for(i=0;i<N;i++)
		rowSum[i]=colSum[i]=0;
	printf("Enter chunk size and no of threads: ");
	scanf("%d%d",&chunk,&nthreads);
	
	#pragma omp parallel shared(a,rowSum,colSum,N) private(i,j) num_threads(nthreads)
		#pragma omp for collapse(2) schedule(static,chunk) ordered
		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
			{
				rowSum[i]+=a[i][j];
				colSum[j]+=a[i][j];
			}
	for(i=0;i<N;i++)
		printf("row[%d] sum = %d \t col[%d] sum = %d \n",i,rowSum[i],i,colSum[i]);
	
	return 0;
}
