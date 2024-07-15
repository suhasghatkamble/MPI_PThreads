#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MATRIX_SIZE 100

int main(int argc, char **argv) {
    int i, j, myid, size, n = MATRIX_SIZE;
    int **m1, **m2, **sumMat;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Allocate memory for matrices
    m1 = (int **)malloc(sizeof(int *) * n);
    m2 = (int **)malloc(sizeof(int *) * n);
    sumMat = (int **)malloc(sizeof(int *) * n);

    for (i = 0; i < n; i++) {
        m1[i] = (int *)malloc(sizeof(int) * n);
        m2[i] = (int *)malloc(sizeof(int) * n);
        sumMat[i] = (int *)malloc(sizeof(int) * n);
    }

    // Initialize matrices m1 and m2
    if (myid == 0) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                m1[i][j] = 1;
                m2[i][j] = 1;
            }
        }
    }

    // Broadcast matrices m1 and m2 to all processes
    MPI_Bcast(&(m1[0][0]), n * n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&(m2[0][0]), n * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Start timing after data distribution
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    // Perform matrix addition in parallel
    int chunk_size = n / size;
    int *sendbuf_m1 = (int *)malloc(sizeof(int) * n * chunk_size);
    int *sendbuf_m2 = (int *)malloc(sizeof(int) * n * chunk_size);
    int *recvbuf_sum = (int *)malloc(sizeof(int) * n * chunk_size);

    // Scatter rows of matrices m1 and m2 to all processes
    MPI_Scatter(&(m1[0][0]), n * chunk_size, MPI_INT, sendbuf_m1, n * chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(&(m2[0][0]), n * chunk_size, MPI_INT, sendbuf_m2, n * chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform local matrix addition
    for (i = 0; i < chunk_size; i++) {
        for (j = 0; j < n; j++) {
            recvbuf_sum[i * n + j] = sendbuf_m1[i * n + j] + sendbuf_m2[i * n + j];
        }
    }

    // Gather results from all processes
    MPI_Gather(recvbuf_sum, n * chunk_size, MPI_INT, &(sumMat[0][0]), n * chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // End timing after all processes have completed
    MPI_Barrier(MPI_COMM_WORLD);
    end_time = MPI_Wtime();

    // Print timing information from process 0
    if (myid == 0) {
        printf("Time taken: %f seconds\n", end_time - start_time);
    }

    // Free dynamically allocated memory
    free(m1);
    free(m2);
    free(sumMat);
    free(sendbuf_m1);
    free(sendbuf_m2);
    free(recvbuf_sum);

    MPI_Finalize();

    return 0;
}
