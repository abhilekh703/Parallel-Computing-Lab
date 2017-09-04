
#include <stdio.h>
#include <omp.h>

int main(int argc, char const *argv[])
{
	int n,i,j;
	float sum=0;
	float newSal[n],compExp[n];
	printf("Enter no of employess: ");
	scanf("%d",&n);
	float arr[n][2];
	printf("Enter the emp id and salary of each employee: ");
	for(i=0;i<n;i++)
		for(j=0;j<2;j++)
			scanf("%f",&arr[i][j]);

	#pragma omp parallel shared(n,arr,newSal,compExp) num_threads(4)
		#pragma omp for ordered private(i) schedule(static,3) reduction(+:sum)
		for(i=0;i<n;i++)
		{
			newSal[i]=arr[i][1]+0.06*arr[i][1];
			if(0.06*arr[i][1] > 5000)
				newSal[i]=newSal[i]-0.02*0.06*arr[i][1];
			compExp[i]=newSal[i]-arr[i][1];
			sum+=compExp[i];
		}
		
	printf("new array\n");
	for(i=0;i<n;i++)
		printf("%f\n",newSal[i]);
	printf("\n%f\n",sum);
	return 0;
}
