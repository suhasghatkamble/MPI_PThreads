#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define N 100000


int main()
{
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *arr = (int*)malloc(N * sizeof(int));
    int *arr1 = (int*)malloc(N * sizeof(int));
    int chunk_size = N / size;
    int *arr2 = (int*)malloc(chunk_size * sizeof(int));



    if (rank == 0)
    {
        for (int i = 0; i < N; i++)
        {
            arr[i] = i;
            arr1[i] = i;
        }
        
    }

    if (rank != 0)
    {
        for (int i = 0; i < N; i++)
        {
            arr2[i] = arr[i] + arr1[i];
        }
        
    }
    
    


}