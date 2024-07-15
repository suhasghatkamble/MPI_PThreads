// #include<stdio.h>
// #include<stdlib.h>
// #include<pthread.h>
// #include<unistd.h> // for using sleep(1)
// #define N 16
// long arr[N];

// void* threadidnumber(void* threadId){
//     long tid = (long)threadId;

//     long arr[N];
//     arr[tid]=tid;    
//     return NULL;
// }

// int main(){
//     pthread_t t[N];

//     for (long i = 0; i < N; i++){
//         pthread_create(&t[i], NULL, threadidnumber, (void*) i);
//     }

//     // Wait for all threads to finish
//     for (long i = 0; i < N; i++){
//             printf("Thread %ld is printing %ld\n", tid, arr[i] );

//     }

//     return 0;
// }








#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N 16
int arr[N];
void* hello(void* threadId){
    long tid = (long)threadId; 
    printf("Thread id %ld is printing %d\n", tid, arr[tid]);
    
    return NULL;
}

int main(){
    pthread_t t[N];
    for (int  i = 0; i < N; i++){
        arr[i] = i;
    }
    

    for (long i = 0; i < N; i++){
        pthread_create(&t[i], NULL, hello, (void*) i);
    }                                               //create new thread

    for (long i = 0; i < N; i++){
        pthread_join(t[i], NULL);                   //to free resources after joining
    }
    
    return 0;
    
}

// 
// gcc -std=gnu99 threadsize.c -o threadsize -pthread
// ./threadsize
