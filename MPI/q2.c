#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN 100000
// global variable 
int X[LEN], Y[LEN], Xd[LEN], Yd[LEN];
int a = 2;

void fillArrays()
{
    for (int i = 0; i < LEN; i++)
    {
        X[i] = rand()%5;
        Xd[i] = X[i];
        Y[i] = rand()%5;
        Yd[i] = Y[i];
    }
}

int main(int argc, char* argv[])
{
    int rank, numP;
    double t1 = MPI_Wtime();
    // single process ---> sequential process
    for (int i = 0; i < LEN; i++)
    {
            Xd[i] = a*Xd[i] + Yd[i];
    }
    t1 = MPI_Wtime() - t1;
    // now here parallely process starts
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numP);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) printf("No. of processes: %d\n", numP);
    // rank 0 process will only print this .
    
    MPI_Barrier(MPI_COMM_WORLD);
    double t2 = MPI_Wtime();
    for (int i = rank; i < LEN; i+=numP)
    {
        X[i] = a*X[i] + Y[i];
    }
    MPI_Barrier(MPI_COMM_WORLD);
    t2 = MPI_Wtime() - t2;
    //printf("Rank: %d out of %d Processes\n", rank, numP);

    MPI_Barrier(MPI_COMM_WORLD);
    
    
    MPI_Barrier(MPI_COMM_WORLD);
   

    if (rank == 0)
    {
        printf("Time taken for sequential: %lf\n", t1);
        printf("Time taken for Parallel : %lf\n", t2);        
        printf("%lf times faster\n", t1/t2);
    }    

    MPI_Finalize();

    return 0;
}
