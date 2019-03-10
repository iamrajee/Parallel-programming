#include <mpi.h>
#include <stdio.h>

typedef struct Partstruct
{
    char c;
    double d[6];
    char b[7];
} Partstruct;

int main(int argc, char *argv[])
{
    int count = 3;
    int blocklengths[3] = { 1, 6, 7 };
    MPI_Aint displacements[] = {offsetof(Partstruct, c),offsetof(Partstruct, d),offsetof(Partstruct, b)};
    MPI_Datatype types[3] = { MPI_CHAR, MPI_DOUBLE, MPI_CHAR };
    MPI_Datatype Particletype;

    MPI_Init(&argc, &argv);
    MPI_Type_create_struct(count, blocklengths, displacements, types, &Particletype);
    MPI_Type_commit(&Particletype);

    int myrank,size;
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    Partstruct particle[1000];

    if (myrank == 0)
    {
        MPI_Send(particle, 1000, Particletype, 1, 123, MPI_COMM_WORLD);
    }
    else if (myrank == 1)
    {
        MPI_Recv(particle, 1000, Particletype, 0, 123, MPI_COMM_WORLD, &status);
    }
    MPI_Finalize();
    return 0;
}

// struct foo(){
//     float value;
//     char rank;
// }
// int count = 2;
// int array_of_blocklengths[] = { 1, 1 };
// MPI_Aint array_of_displacements[] = { offsetof( foo, value ),
//                                       offsetof( foo, rank ) };
// MPI_Datatype array_of_types[] = { MPI_FLOAT, MPI_CHAR };
// MPI_Datatype tmp_type, my_mpi_type;
// MPI_Aint lb, extent;

// MPI_Type_create_struct( count, array_of_blocklengths, array_of_displacements,
//                         array_of_types, &tmp_type );
// MPI_Type_get_extent( tmp_type, &lb, &extent );
// MPI_Type_create_resized( tmp_type, lb, extent, &my_mpi_type );
// MPI_Type_commit( &my_mpi_type );
// MPI_Type_free   ( &tmp_type );

/*
MPI_Aint      a_addr, b_addr, n_addr;

// Get the addresses of the members
MPI_Get_address (a_p, &a_addr);
MPI_Get_address (b_p, &b_addr);
MPI_Get_address (n_p, &n_addr);

// Get the offsets from the starting address of the first element
array_of_displacements[1] = b_addr - a_addr;
array_of_displacements[2] = n_addr - a_addr;
*/