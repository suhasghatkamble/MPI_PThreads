#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define N 1000
long sum=0;


void* hello(void* threadId){
    long tid = (long)threadId; 
    sum=sum+tid;
    return NULL;
}

int main(){
    pthread_t t[N];
    // t = malloc(sizeof(pthread_t) * N);
    for (long  i = 0; i < N; i++)
    {
        pthread_create(&t[i], NULL, hello, (void*) i);
    }

     for (long i = 0; i < N; i++){
        pthread_join(t[i], NULL);                 
    }
    
    printf("Sum is : %d", sum+N);
    printf("Expected sum : %d", N*(N+1)/2);
    // free(t);
    return 0;
}