#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<omp.h>
#include<pthread.h>



//hybrid 
//mpi inside openmp

int main(int argc, char* argv[])
{
    int thread_provided;
    int provided = MPI_THREAD_MULTIPLE;
    int thread_level = MPI_Init_thread(&argc, &argv, provided, &thread_provided);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // Check the level of thrad support provided by MPI

    if (thread_level != MPI_SUCCESS)
    {
        printf("Error initializing MPI threads \n");
        return 1;
    }

    if (thread_provided != MPI_THREAD_MULTIPLE)
    {
        printf("Warnig: MPI_THREAD_MULTIPLE requested but not provided \n");
    }

    #pragma omp parallel num_threads(4)
    {
        printf("Hello openmp from thread %d inside process %d\n", omp_get_thread_num(), rank);
    }
    

    MPI_Finalize();
    
    return 0;
}

//mpicc mpi_INIT_THREAD.c -fopenmp
//mpirun -np 2 ./a.out