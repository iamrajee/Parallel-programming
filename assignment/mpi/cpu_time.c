#include <stdio.h>   // printf()
#include <mpi.h>     // MPI
#include <unistd.h>  // sleep()

#define  MASTER 0

int solveProblem(int id, int numProcs) {

    sleep( ((double)id+1) / numProcs);

    return 42;
}

int main(int argc, char** argv) {
    int id = -1, numProcesses = -1;
    double startTime = 0.0, localTime = 0.0, totalTime = 0.0;
    int answer = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    MPI_Barrier(MPI_COMM_WORLD);
    startTime = MPI_Wtime();

    answer = solveProblem(id, numProcesses);

    localTime = MPI_Wtime() - startTime;
    MPI_Reduce(&localTime, &totalTime, 1, MPI_DOUBLE,
        MPI_MAX, 0, MPI_COMM_WORLD);

    if ( id == MASTER ) {
        printf("\nThe answer is %d; computing it took %f secs.\n\n",
                   answer, totalTime);
    }

    MPI_Finalize();
    return 0;
}