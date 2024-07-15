#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <mpi.h>

#define N 999999999

int main(int argc, char **argv)
{
    int i, j, num_procs, my_rank;
    double area, pi;
    double dx, y, x;
    double exe_time;
    double local_area; 

    struct timeval stop_time, start_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    dx = 1.0/N;
    x = 0.0;
    area = 0.0;
    local_area = 0.0;

    gettimeofday(&start_time, NULL);

    for(i=my_rank;i<N;i+=num_procs)
    {
        x = i*dx;
        y = sqrt(1-x*x);
        local_area += y*dx;
    }

    MPI_Allreduce(&local_area, &area, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    gettimeofday(&stop_time, NULL);
    exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));

    if(my_rank == 0)
    {
        pi = 4.0*area;
        printf("\n Value of pi is = %.16lf\n Execution time is = %lf seconds\n", pi, exe_time);
    }

    MPI_Finalize();

    return 0;
}