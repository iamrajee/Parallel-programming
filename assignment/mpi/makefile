SHELL=/bin/bash
MPICC?=mpicc
programlist=MPI_Send_and_Recv MPI_Reduce MPI_Allreduce MPI_Bcast MPI_Scatter_and_Gather MPI_Scatter_and_Allgather MPI_Barrier cpu_time MPI_Type_create_struct
all:
	make clean
	make run
clean:
	rm -f *.out
run:
	$(foreach x,$(programlist),${MPICC} -g -Wall -o $(x).out $(x).c;)
	bash bash.sh