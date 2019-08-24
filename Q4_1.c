#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main()
{
 	int i=0,j=0,k=0,l=0,m=0,n1=0,t=1000;
	long a[t][t],b[t][t],c[t][t];
	
	double start_t=0,end_t=0;
	// input 
	srand(time(0));	
	for(m=0;m<t;m++)
		for(l=0;l<t;l++)
		{
			a[m][l]=rand();
			b[m][l]=rand();
		}
		// sequential matrix mul
		start_t=omp_get_wtime();
		for(i=0;i<t;i++)
		for(j=0;j<t;j++)
			for(k=0;k<t;k++)
			{
				c[i][j]+= a[i][k]*b[k][j];
			}
		end_t=omp_get_wtime();
		printf("Execution time having %d threads is %.15lf\n",n1,end_t-start_t);
		// parallel mm	
	omp_set_num_threads(8);
	start_t=omp_get_wtime();
	#pragma omp parallel
	{
		int ID=omp_get_thread_num();
		int ID1=omp_get_thread_num();
		int n=omp_get_num_threads();
		for(i=ID;i<t;i+=n)
		for(j=ID1;j<t;j+=n)
			for(k=0;k<t;k++)
			{
				c[i][j]=c[i][j] + a[i][k]*b[k][j];
			}
		n1=n;

	}
	end_t=omp_get_wtime();
	printf("Execution time having %d threads is %.15lf\n",n1,end_t-start_t);
return 0;
}