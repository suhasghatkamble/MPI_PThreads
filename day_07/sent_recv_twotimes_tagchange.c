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
                //Tag change for number2 
                // Tag identified correct received from sent
                // SYSTEM_BUFFER involved
    int number;
    int number1;

    if (rank == 0)
    {
        number = 100;
        number1 = 200;
        
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&number1, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);

       
        printf("Process 0 sent number %d to process 1\n", number);
        printf("Process 0 sent number1 %d to process 1\n", number1);


        MPI_Recv(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&number1, 1, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 0 received number %d from process 1\n", number);
        printf("Process 0 received number1 %d from process 1\n", number1);

        
    } else if (rank == 1){

        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&number1, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 1 received number %d from process 0\n", number);
        printf("Process 1 received number1 %d from process 0\n", number1);

        int number = 300;
        int number1 = 400;

        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&number1, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);

        printf("Process 1 sent number %d to process 0\n", number);
        printf("Process 1 sent number1 %d to process 0\n", number1);


    }
     else{
        printf("I am process %d and I have nothing to do\n", rank);
     }



    MPI_Finalize();
    return 0;  
}