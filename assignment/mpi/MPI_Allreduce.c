#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv)
{
    int size, rank;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int localsum[2] = {0,0};//=> count = 2
    int globalsum[2] = {0,0};

    if(rank % 2 == 1)
    {
        localsum[0] += 5;
    }
    else if( rank > 0 && (rank % 2 == 0))
    {
        localsum[1] += 10;
    }
    //here count = 2,(size of variable(say array) we are passing)
    //here dont pass the destination as it is going to all
    MPI_Allreduce(localsum,globalsum,2,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

    printf("rank = %d,  globalsum = {%d,%d} \n",rank,globalsum[0],globalsum[1]);

    MPI_Finalize();

    return (EXIT_SUCCESS);
}