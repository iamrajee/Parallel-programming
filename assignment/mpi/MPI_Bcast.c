#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
        int rank;
        int buf[2];
        const int root=0;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if(rank == root) {
           buf[0] = 11;
           buf[1] = 22;
        }

        printf("[%d]: Before Bcast, buf is {%d,%d}\n", rank, buf[0], buf[1]);

        /* everyone calls bcast, data is taken from root and ends up in everyone's buf */
        MPI_Bcast(&buf, 2, MPI_INT, root, MPI_COMM_WORLD);

        printf("[%d]: After Bcast, buf is {%d,%d}\n", rank, buf[0], buf[1]);

        MPI_Finalize();
        return 0;
}