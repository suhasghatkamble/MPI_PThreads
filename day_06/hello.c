#include<mpi.h>
#include <unistd.h>
#include<stdio.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv); 
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    printf("Hello from process %d of %d\n", world_rank, world_size);
   printf("``````````````````\n");
    MPI_Finalize();
    // sleep(60);
    printf("afterfinalize %d of %d\n", world_rank, world_size);
printf("*******\n");
    return 0;
}