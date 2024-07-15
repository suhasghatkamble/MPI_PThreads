#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int n = 10;
    int i, j, k;

    MPI_Init(&argc, &argv);
    int num_procs, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int local_n = n / num_procs;
    int start_row = rank * local_n;
    int end_row = start_row + local_n;

    if (rank == num_procs - 1) {
        end_row = n;
    }

    int **local_A = (int **)malloc(local_n * sizeof(int *));
    int **local_B = (int **)malloc(n * sizeof(int *)); 
    int **local_C = (int **)malloc(local_n * sizeof(int *));
    
    for (i = 0; i < local_n; i++) {
        local_A[i] = (int *)malloc(n * sizeof(int));
        local_C[i] = (int *)malloc(n * sizeof(int));
    }

    int **A = NULL;
    if (rank == 0) {
        A = (int **)malloc(n * sizeof(int *));
        for (i = 0; i < n; i++) {
            A[i] = (int *)malloc(n * sizeof(int));
            for (j = 0; j < n; j++) {
                A[i][j] = 1;
            }
        }
    }

    MPI_Bcast(&A[0][0], n*n, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < n; i++) {
        local_B[i] = (int *)malloc(n * sizeof(int));
        for (j = 0; j < n; j++) {
            local_B[i][j] = 1;
        }
    }

    MPI_Scatter(&local_B[0][0], local_n * n, MPI_INT, &local_B[0][0], local_n * n, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < local_n; i++) {
        for (j = 0; j < n; j++) {
            local_C[i][j] = 0;
            for (k = 0; k < n; k++) {
                local_C[i][j] += local_A[i][k] * local_B[k][j];
            }
        }
    }

    MPI_Gather(&local_C[0][0], local_n * n, MPI_INT, &A[0][0], local_n * n, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < local_n; i++) {
        free(local_A[i]);
        free(local_C[i]);
    }
    free(local_A);
    free(local_B);
    free(local_C);

    if (rank == 0) {
        for (i = 0; i < n; i++) {
            free(A[i]);
        }
        free(A);
    }

    MPI_Finalize();

    return 0;
}




