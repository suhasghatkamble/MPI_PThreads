#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 100000

int main()
{
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int *arr = (int*)malloc(N * sizeof(int));
    int chunk_size = N/size;

    if (rank == size - 1 )
    {
        chunk_size = chunk_size + N % size;
    }

    int *arr1 = (int*)malloc(chunk_size * sizeof(int));

    if (rank == 0)
    {
        for (int i = 0; i < N; i++)
        {
           arr[i] = i;
        }
    }
    
    MPI_Scatter(arr, chunk_size, MPI_INT, arr1, chunk_size, MPI_INT, 0, MPI_COMM_WORLD); 

    printf("Process %d received data %d\n", rank, arr1[1000]);

    free(arr);
    free(arr1);
    MPI_Finalize();
    return 0;

}