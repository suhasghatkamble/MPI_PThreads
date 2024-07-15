// #include <mpi.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char** argv) {
//     int rank, size;
//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);

//     int* process_id;

//     if (rank == 0) {
//         process_id = (int*) malloc(size * sizeof(int));
//     }

//     MPI_Gather(&rank, 1, MPI_INT, process_id, 1, MPI_INT, 0, MPI_COMM_WORLD);

//     if (rank == 0) {
//         int total_sum = 0;
//         for (int i = 0; i < size; i++) {
//             total_sum += process_id[i];
//         }
//         printf("Total process sum: %d\n", total_sum);
//         free(process_id);
//     }

//     MPI_Finalize();
//     return 0;
// }


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int total_sum;

    MPI_Reduce(&rank, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total process sum: %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}


