#include<mpi.h>
#include<stdio.h>

int main(int argc, char **argv) {
    int myid, size;
    int myval;
    MPI_Init(&argc, &argv);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); 
    // Process with ID exactly equal to 0
    if (myid==0)
    {
        //Initialize data to be sent
        myval = 100;
        //Print the data to be sent
        printf("\n myid:%d \t myval = %d", myid, myval);
        //Send data
        MPI_Send(&myval, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("\n my id: %d \t Data sent.\n ", myid);
    }
    else if(myid==1){// Process with ID exactly equal to 1
    //Initialize receive array to some other data
    myval = 200;
    MPI_Recv(&myval, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("\nmyid: %d \t Data received.", myid);
    //Print received data
    printf("\nmyid: %d \t myval = %d", myid, myval);
    printf("\n\nProgram exit!\n");
    }
      MPI_Finalize();

    return 0;
}