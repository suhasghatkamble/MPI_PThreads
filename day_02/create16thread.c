//  Creating 2 or more thread


#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h> // for using sleep(1)
#define N 16
void* hello(void* threadId){
    long tid = (long)threadId; 
    printf("Forking %ld of %d\n", tid, N);
    sleep(1);
    printf("Joining %ld of %d\n", tid, N);
    return NULL;
}

int main(){
    pthread_t t[N];

    for (long i = 0; i < N; i++){
        pthread_create(&t[i], NULL, hello, (void*) i);
    }

    for (long i = 0; i < N; i++){
        pthread_join(t[i], NULL);
    }
    
    return 0;
    
}
// gcc -std=gnu99 create16thread.c -o create16 -pthread
// ./create16