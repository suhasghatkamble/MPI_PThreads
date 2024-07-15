// #include<stdio.h>
// #include<mpi.h>
// #include<stdlib.h>
// #include<omp.h>
// #include<pthread.h>
// #define N 16
// int arr[N];


// void* hello(void* threadId){
//     long tid = (long)threadId; 
//     printf("Thread id %ld is printing %d\n", tid, arr[tid]);
    
//     return NULL;
// }


// int main(int argc, char* argv[])
// {
//     int thread_provided;
//     int provided = MPI_THREAD_MULTIPLE;
//     int thread_level = MPI_Init_thread(&argc, &argv, provided, &thread_provided);
//     int rank, size;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);


//     pthread_t t[N];
//     for (int  i = 0; i < N; i++){
//         arr[i] = i;
//     }
    

//     for (long i = 0; i < N; i++){
//         pthread_create(&t[i], NULL, hello, (void*) i);
//     }                                              

//     for (long i = 0; i < N; i++){
//         pthread_join(t[i], NULL);                   
//     }
    


//     MPI_Finalize();
    
//     return 0;
// }



// #include<stdio.h>
// #include<mpi.h>
// #include<stdlib.h>
// #include<omp.h>
// #include<pthread.h>
// #define N 5
// int arr[N];


// void* hello(void* a){
//     long tid = (long)a;
//     int rank = *((int*)a + 1);  // Extract rank from the argument
    
//     printf("MPI Rank %d, Thread id %ld is printing %d\n", rank, tid, arr[tid]);
    
//     return NULL;
// }


// int main(int argc, char* argv[])
// {
//     int thread_provided;
//     int provided = MPI_THREAD_MULTIPLE;
//     int thread_level = MPI_Init_thread(&argc, &argv, provided, &thread_provided);
//     int rank, size;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);


//     pthread_t t[N];
//     int args[N][2];  // Array to hold arguments for threads

//     for (int  i = 0; i < N; i++){
//         arr[i] = i;
//     }
    

//     for (long i = 0; i < N; i++){
//         args[i][0] = i;  // thread id
//         args[i][1] = rank;  // MPI rank
//         pthread_create(&t[i], NULL, hello, (void*)args[i]);
//     }                                              

//     for (long i = 0; i < N; i++){
//         pthread_join(t[i], NULL);                   
//     }
    

//     MPI_Finalize();
    
//     return 0;
// }



#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<omp.h>
#include<pthread.h>
#define N 16
int arr[N];


void* hello(void* arg){
    long tid = (long)arg;  // Cast arg back to long
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Get MPI rank

    printf("MPI Rank %d, Thread id %ld is printing %d\n", rank, tid, arr[tid]);

    return NULL;
}


int main(int argc, char* argv[])
{
    int thread_provided;
    int provided = MPI_THREAD_MULTIPLE;
    int thread_level = MPI_Init_thread(&argc, &argv, provided, &thread_provided);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    pthread_t t[N];

    for (int  i = 0; i < N; i++){
        arr[i] = i;
    }
    

    for (long i = 0; i < N; i++){
        pthread_create(&t[i], NULL, hello, (void*) i);
    }                                              

    for (long i = 0; i < N; i++){
        pthread_join(t[i], NULL);                   
    }
    

    MPI_Finalize();
    
    return 0;
}
