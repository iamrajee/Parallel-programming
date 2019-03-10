#include <mpi.h>
#include <stdio.h> 
int main(int argc, char *argv[]) 
{ 
    int rank, size;

    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&size); 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    printf("Hi from %d\n", rank);fflush(stdout); 
    printf("Process %d doing task1!\n",rank);

    MPI_Barrier(MPI_COMM_WORLD);
    printf("Process %d doing task2!\n",rank);    //random order

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    for ( int i = 0; i < size; ++i ) {  //enforces order allthough
    if ( rank == i ) {
        // my turn to write to terminal
        printf("Bye from %d\n",rank);
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

    MPI_Finalize(); 
    return 0; 
} 