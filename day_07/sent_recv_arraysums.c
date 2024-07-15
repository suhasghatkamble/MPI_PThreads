#include<mpi.h>
#include<stdio.h>

#define N 1000

int main(int argc, char** argv){
    int arr[N];//this data get to all process , so all each process get 1000 data  //so if 4 process 4000 data create (not good)
    for (int i = 0; i < N; i++)
    {
        arr[i] = i + 1;
    }


    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int chunkSize = N / size;
    int start = chunkSize * rank;
    int end = (rank + 1) * chunkSize;
    // int end = start + chunkSize;

    if (size < 2)
    {
        fprintf(stderr, "World size must be greater than 1 for this example \n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int localSum = 0;
    for (int i = start; i < end; i++)
    {
        localSum = localSum + arr[i];
    }

    int number;

    if (rank != 0)
    {
        MPI_Send(&localSum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    if (rank == 0)
    {
        int totalSum = 0;
        totalSum += localSum;
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(&localSum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            totalSum+=localSum;
        }

        printf("Total sum = %d\n", totalSum);
    } 
    else if (rank == 1){

        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 1 received number %d from process 0\n", number);


    }
    MPI_Finalize();
    return 0;  
}













// #include<mpi.h>
// #include<stdio.h>

// #define N 1000

// int main() {
//     int size;
//     int arr[N];
//     int local_sum;
//     int chunksize;
//     int rank;


//     MPI_Init(NULL, NULL);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank); 

//     if (rank==0)
//     {
//         for (int i = 0; i < N; i++) 
//         arr[i]=i+1;
        
        
//         MPI_Send(arr, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
//         printf("Process 0 sent to process 1", rank);
//     }
//     else if(rank==1){

//     MPI_Recv(arr, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//     printf("\nmyid: %d \t Data received.\n", myid);

//     int chunksize = N/size;
//     int start = rank + chunksize;
//     int end = start * (chunksize+1);
//     for (int i = start; i < end; i++)
//     {
//         local_sum+=arr[i];
//     }
//     printf("\n\nProgram exit!\n");

//     }
//       MPI_Finalize();

//     return 0;
// }


