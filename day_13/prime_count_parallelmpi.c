#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>

#define N 1000

int main(int argc, char** argv) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int i, j;
    int count, flag;
    double exe_time;
    struct timeval start_time, stop_time;

    count = 1; 

    gettimeofday(&start_time, NULL);

    int start = rank * (N - 2) / size + 2;
    int end = (rank + 1) * (N - 2) / size + 2;

    int local_count = 0;

    for (i = start; i < end; i++) {
        flag = 0;
        for (j = 2; j * j <= i; j++) {
            if ((i % j) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            local_count++;
        }
    }

    int global_count;
    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec + (stop_time.tv_usec / 1000000.0)) - (start_time.tv_sec + (start_time.tv_usec / 1000000.0));

    if (rank == 0) {
        printf("\n Number of prime numbers = %d \n Execution time is = %lf seconds\n", global_count, exe_time);
    }

    MPI_Finalize();
    return 0;
}