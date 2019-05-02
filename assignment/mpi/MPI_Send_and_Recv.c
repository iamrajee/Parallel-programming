/*
See also
MPI_Ssend
MPI_Isend
MPI_Test
MPI_Wait
MPI_Sendrecv
*/

#include <stdio.h>
#include <string.h>
#include<time.h>
#include <mpi.h>       // for MPI functions

const int MAX_STRING = 100;

int main(int argc, char* argv[]) {
    //clock_t tStart = clock(); //starting clock //in c can only be used inside main()
    char msg[MAX_STRING];
    int  comm_sz;         // Number of processes
    int my_rank;          // My process rank
    
    MPI_Init(NULL, NULL);
    // MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    
    if (my_rank != 0) {
        sprintf(msg, "Process %d of %d: Hello World! from processor %s", my_rank, comm_sz,processor_name);
        MPI_Send(msg, strlen(msg)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    else {
        printf("Process %d of %d: Hello World! from processor %s\n", my_rank, comm_sz,processor_name);
        for (int i = 1; i < comm_sz; i++) {
            MPI_Recv(msg, MAX_STRING, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", msg);
        }
    }
    
    MPI_Finalize();
    //printf("\n%f",(double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
