#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<omp.h>



//hybrid 
//mpi inside openmp

int main()
{
    int size, rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    omp_set_num_threads(4);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Hello World from thread %d , process %d\n", thread_id, rank);
    }




    MPI_Finalize();

    return 0;


}