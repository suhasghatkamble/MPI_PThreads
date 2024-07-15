#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 10000


int main() {
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *arr =(int*)malloc(N * sizeof(int));


    if (rank==0)
    {
        for (int i = 0; i < N; i++)
        {
            arr[i]=i;
        }
    }
    MPI_Bcast(arr, N, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Process %d received data %d\n", rank, arr[1000]);



    free(arr);
    MPI_Finalize();
        
    
    
}