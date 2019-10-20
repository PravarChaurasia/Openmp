#include <omp.h>
#include<stdio.h>
void main()
{
		int a=0,b=0,c=0,d=0;
		scanf("%d %d",&a,&b);
		
	#pragma omp parallel
	{
		
		int ID=omp_get_thread_num();
		switch(ID)
		{
			case 0:	 printf("Hello(%d)",ID);
					 printf("World(%d)\n",ID);
					 break;
			case 1:c=a+b;
					printf("%d(%d)\n",c,ID);
					break;
			case 2:d=a-b;
					printf("%d(%d)\n",d,ID);
					break;
		}
		
	}
	a=c;
	b=d;
	#pragma omp parallel
	{
		int ID=omp_get_thread_num();
		switch(ID)
		{
			case 3:c=a+b;
					printf("%d(%d)\n",c,ID);
					break;
			case 4:d=a-b;
					printf("%d(%d)\n",d,ID);
					break;
		}
		
	}
}
