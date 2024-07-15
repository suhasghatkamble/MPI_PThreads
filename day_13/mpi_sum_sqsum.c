#include <mpi.h>
#include <stdio.h>

#define N 10

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int arr[N];

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    for (int i = 0; i < N; ++i) {
        arr[i] = i + 1; 
    }

    int color = world_rank % 2;  
    MPI_Comm new_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &new_comm);

    int new_rank, new_size;
    MPI_Comm_rank(new_comm, &new_rank);
    MPI_Comm_size(new_comm, &new_size);

    if (color == 0) {
        int local_sum = 0;
        for (int i = 0; i < N; ++i) {
            local_sum += arr[i];
        } 

        int global_sum;
        MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, new_comm);

        if (new_rank == 0) {
            printf("Communicator 0, World Rank: %d, Sum of Array: %d\n", world_rank, global_sum);
        }
    } 
    
    
    
    
    
    
    else {
        int local_sum_of_squares = 0;
        for (int i = 0; i < N; ++i) {
            local_sum_of_squares += arr[i] * arr[i];
        }

        int global_sum_of_squares;
        MPI_Reduce(&local_sum_of_squares, &global_sum_of_squares, 1, MPI_INT, MPI_SUM, 0, new_comm);

        if (new_rank == 0) {
            printf("Communicator 1, World Rank: %d, Sum of Squares: %d\n", world_rank, global_sum_of_squares);
        }
    }

    MPI_Comm_free(&new_comm);

    MPI_Finalize();
    return 0;
}
