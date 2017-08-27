#include<omp.h>
#include<stdio.h>
int main(){
int i,n,chunk;
int result=0;
int a[20],b[20],c[20];
n=20;
chunk=5;
/*initializing array*/
for(i=0;i<n;i++)
{ a[i]=i*2;
b[i]=i*3;
}
#pragma omp parallel for default(shared) num_threads(4) private(i) schedule(static,chunk) reduction(+:result)
for(i=0;i<n;i++)
result=result+(a[i]*b[i]);

printf("Final result=%d\n",result);
}