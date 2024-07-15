//  Creating 2 or more thread


#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define N 4
void* hello(void* threadId){
    long tid = (long)threadId; //in pthread long datatype used for 64-bit,, (long)--implecite datatype
    printf("Forking %ld of %d\n", tid, N);
    printf("Joining %ld of %d\n", tid, N);
    return NULL;
}

int main(){
    pthread_t t1, t2, t3, t4;

    pthread_create(&t1, NULL, hello, (void*) 0);// void* pointer store everyone address 
    pthread_create(&t2, NULL, hello, (void*) 1);
    pthread_create(&t3, NULL, hello, (void*) 2);
    pthread_create(&t4, NULL, hello, (void*) 3);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL); 
    return 0;
    
}


//               _____________________
// _____________/                     \_________                   _______________________
//                                              \_________________/