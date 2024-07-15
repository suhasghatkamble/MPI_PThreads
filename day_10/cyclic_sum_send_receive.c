#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int recv_rank, send_rank;

    if (rank == 0) {
        send_rank = rank;
        MPI_Send(&send_rank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_rank, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Total rank sum: %d\n", recv_rank);
    } 

    

    else {
        MPI_Recv(&recv_rank, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        send_rank = recv_rank + rank;
        
        if (rank < size-1) {
            MPI_Send(&send_rank, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        } 
        
        else {
            MPI_Send(&send_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    
//mpirun -np 10 --oversubscribe ./a.out

    return 0;
    MPI_Finalize();
}
