#include<mpi.h>
#include<stdio.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2)
    {
        fprintf(stderr, "World size must be greater than 1 for this example \n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int number;
    int number2;

    if (rank == 0)
    {
        number = 25;
        MPI_Request request;
        MPI_Isend(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        //MPI_Wait(&request, MPI_STATUS_IGNORE);
        printf("Process 0 sent number %d to process 1\n", number);

        MPI_Irecv(&number2, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        printf("Receive from process 1 , number = %d\n", number2);
        
    } else if (rank == 1){

        MPI_Request request;
        MPI_Irecv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        printf("Process 1 received number %d from process 0\n", number);

        int number2 = 28;

        MPI_Isend(&number2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        printf("Sent to process 0 , number = %d\n", number2);

    }



    MPI_Finalize();
    return 0;  
}