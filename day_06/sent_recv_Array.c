#include<mpi.h>
#include<stdio.h>

#define N 21

int main() {
    int myid, size;
    int myval;
    int arr[N];



    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); 

    if (myid==0)//process 0 will execute this
    {
        for (int i = 0; i < N; i++) arr[i]=i+1;
        
        
        MPI_Send(arr, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("\n my id: %d \t Data sent.\n ", myid);
    }
    else if(myid==1){ //process 1 will execute this
        // Process with ID exactly equal to 1
    //Initialize receive array to some other data

    // int receive_arr[N];
    MPI_Recv(arr, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("\nmyid: %d \t Data received.\n", myid);

    for (int i = 0; i < N; i++) printf("%d ", arr[i]);
    
    
    //Print received data
    printf("\n\nProgram exit!\n");
    }
      MPI_Finalize();

    return 0;
}