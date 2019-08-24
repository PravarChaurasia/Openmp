#include<stdio.h>
#include<omp.h>
void hello(int ID)
{
	printf("Hello(%d)",ID);
	printf("World(%d)\n",ID);
}
void main()
{
 	#pragma omp parallel
 	{
 	 	int ID=omp_get_thread_num();
 	 	hello(ID);
 	}
}
