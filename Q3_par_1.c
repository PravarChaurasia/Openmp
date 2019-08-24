#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
void fn(int ID,int n,long *a,long *b)
{
	for(int i=ID;i<65536;i=i+n)
		a[i]=256*a[i]+b[i];
}
void main()
{

	#ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output.txt", "w", stdout);
	#endif
	
	long a[65536],b[65536];
	double start_t=0,end_t=0;
	srand(time(0));
	for(int i=0;i<65536;i++)
	{
		a[i]=rand();
		b[i]=rand();
	}
	omp_set_num_threads(10);
	start_t=omp_get_wtime();
	int n1=0;
	#pragma omp parallel
	{
		int ID=omp_get_thread_num();
		int n=omp_get_num_threads();
		fn(ID,n,a,b);
		n1=n;

	}
	end_t=omp_get_wtime();
	printf("Execution time having %d threads is %.15lf\n",n1,end_t-start_t);
}