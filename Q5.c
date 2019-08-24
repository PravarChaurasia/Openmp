#include <omp.h>
#include<stdio.h>
#include<stdlib.h>
// first see graph of pi.
int main()
{
	long count=100000000; // x will be divided in 10000 such the delta(x)=1/10000;
	int x=0,n1=0;
	double dx=1.0/(double)count,sum=0,pi=0;
	double start_t=0,end_t=0;
	start_t=omp_get_wtime();
	for(int i=0;i<count;i++)
	{
		x= (i+ 0.5)*dx;  //f(xi) at that point ,taken 0.5 bcoz xi will be the mid point of delta(x).
		sum+= 4.0/(1.0+x*x);

	}
	pi=sum*dx;
	end_t=omp_get_wtime();
	printf("pi=%.15lf and Execution time having %d threads is %.15lf\n",pi,n1,end_t-start_t);
	// parallel 
	x=0; sum=0;pi=0;
	omp_set_num_threads(4);
	start_t=omp_get_wtime();
	#pragma omp parallel
	{
		int ID=omp_get_thread_num();
		int n=omp_get_num_threads();
		for(int i=ID;i<count;i+=n)
		{
			x=(i+0.5)*dx;
			#pragma omp critical       ///* Critical section - Only one thread modifies Sum at a time.*/
			sum+=4.0/(1.0+x*x);
		}
		n1=n;
	}
	pi=sum*dx;
	end_t=omp_get_wtime();
	printf("pi=%.15lf and Execution time having %d threads is %.15lf\n",pi,n1,end_t-start_t);
return 0;
}