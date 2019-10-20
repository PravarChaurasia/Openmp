#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<omp.h>
int flag=0;
void producer(int a[],int n)
{
	for(int i=0;i<n;i++)
	{
		a[i]=rand()%100+1;
		printf("%d ",a[i]);
	}
	flag=1;
	#pragma omp flush (flag)

}
void consumer(int a[],int n)
{
	
	int sum=0;
	for(int i=0;i<n;i++)
		sum+=a[i];
	printf("sum is %d\n",sum);
	flag=0;
	#pragma omp flush(flag)
}

void main()
{
	int n=2;
	int a[n];
	srand(time(0));
	double start=0,end=0;
	start=omp_get_wtime();
	producer(a,n);
	consumer(a,n);
	end=omp_get_wtime();
	printf("Execution time without parallel programming  %.15lf \n",end-start);

	omp_set_num_threads(2);
	start=omp_get_wtime();
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			while(flag!=0)
			{
			#pragma omp flush(flag)  // check continusly for flag
			}
			producer(a,n);
		}
		#pragma omp section
		{
			while(flag!=1)
			{
			#pragma omp flush(flag)
			}
		consumer(a,n);	
		}
	}
	end=omp_get_wtime();
	printf("Execution time using parallel programming %.15lf \n",end-start);
}