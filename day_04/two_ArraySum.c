// #include<stdio.h>
// #include<pthread.h>

// #define N 100000
// #define T 16
// long sum = 0;



// void *hello(void* threadId){
//     long tid = (long)threadId;
//     long localSum = 0;
//     int chunk_size = N / T;
//     int start = tid * chunk_size;
//     int end = (tid + 1) * chunk_size;
//     if (tid == T - 1) {
//         end = N;
//     }
//     for (int i = start; i < end; i++) {
//         localSum += (long)arr[i];
//     }
//     sum += localSum;
//     return NULL;
// }



// int main(){
//     int sum = 0;
//     int arrA[N];
//     int arrB[N];
//     int arrC[N];

//     for (int i = 1; i <= N; i++)
//     {
//         arrA[i]=i;
//         arrB[i]=i;
//     }

//     for (int i = 1; i <= N; i++)
//     {
//         arrC[i]=arrA[i]+arrB[i];
//     }

//     for (int i = 1; i <= N; i++)
//     {
//        printf("Array A : %d and Array B : %d is Array C : %d \n",arrA[i], arrB[i], arrC[i]);
//     }
    
//     pthread_t* t;
//     t = malloc(sizeof(pthread_t)*N);



//     for(long i = 0; i < T; i++)
//         pthread_create(&t[i], NULL, hello, (void*)i);
//     for(long i = 0; i < T; i++)
//         pthread_join(t[i], NULL);
    

//     return 0;
// }




//Addition of Two Array



// // Initialize array of size N. Calculate sum of all the elements of the array by using reduction algorithm


// #include<stdio.h>
// #include<stdlib.h>
// #include<pthread.h>

// #define N 3000
// int arr1[N/3];
// int arr2[N/3];
// int arr3[N/3];
// int arr[N];

// pthread_mutex_t mutex; // create mutex variable
// long sum1=0;
// long sum2=0;
// long sum3=0;
// long sum=0;



// void *hello(void* threadId){
//     long tid = (long)threadId;
//     pthread_mutex_lock(&mutex); //give lock
//     sum1 += arr1[tid];
//     pthread_mutex_unlock(&mutex); //unlock
//     return NULL;
// }


// void *hello1(void* threadId){
//     long tid = (long)threadId;
//     pthread_mutex_lock(&mutex); //give lock
//     sum2 += arr2[tid];
//     pthread_mutex_unlock(&mutex); //unlock
//     return NULL;
// }

// void *hello2(void* threadId){
//     long tid = (long)threadId;
//     pthread_mutex_lock(&mutex); //give lock
//     sum3 += arr3[tid];
//     pthread_mutex_unlock(&mutex); //unlock
//     return NULL;
// }


// int main(){
//     pthread_t* t1;
//     pthread_t* t2;
//     pthread_t* t3;

//     for (int i = 0; i < N; i++)
//     {
//         arr[i] = i;
//     }
    

//     pthread_mutex_init(&mutex, NULL); // mutex initialize in main() funtion
//     t1 = malloc(sizeof(pthread_t) * N/3);  //dynamic mem allocation , because heap mem greater than stack
//     t2 = malloc(sizeof(pthread_t) * N/3); 
//     t3 = malloc(sizeof(pthread_t) * N/3); 
    
//     for (long  i = 0; i < N; i++)
//         pthread_create(&t1[i], NULL, hello, (void*) i);
    

//      for (long i = 0; i < N; i++)
//         pthread_join(t1[i], NULL);           



//         for (long  j = 0; j < N; j++)
//         pthread_create(&t2[j], NULL, hello1, (void*) j);
    

//      for (long j = 0; j < N; j++)
//         pthread_join(t2[j], NULL);                 


//     for (long  k = 0; k < N; k++)
//         pthread_create(&t3[k], NULL, hello2, (void*) k);
    

//      for (long k = 0; k < N; k++)
//         pthread_join(t3[k], NULL);                 



//     pthread_mutex_destroy(&mutex); // destroy the lock
    
//     // printf("Sum is : %d \n", sum+N);
//     // printf("Expected sum : %d \n", N*(N+1)/2);

//     sum=sum1+sum2+sum3;
//         printf("Sum is : %d \n", sum+N);



//     free(t1);
//     free(t2);
//     free(t3);

//     return 0;
// }








#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define N 30000
#define T 16

pthread_mutex_t mutex; // create mutex variable
long sum=0;

int arr1; //declare -- we have to dynamically allocate the code
int arr2;
int arr3;




void *hello(void* threadId){
    long tid = (long)threadId;
    long localSum = 0;

    int chunk_size = N/T;
    int start = tid * chunk_size;
    int end = (tid + 1) * chunk_size;

    if (tid == T - 1){
        end = N;
    }

    for (int i = start; i < end; i++)
    {
        arr3[i]=arr1[i]+arr2[i];
    }

    return NULL;
}

int main(){
    pthread_t* t;

    arr1=(int*)malloc(sizeof(int) * N);//allocation
    arr2=(int*)malloc(sizeof(int) * N);
    arr3=(int*)malloc(sizeof(int) * N);


    for (int i = 0; i < N; i++)//initialization
    {
        arr1[i] = i+1;
        arr2[i] = i+1;
        arr3[i]=0;

    }
    

    t = malloc(sizeof(pthread_t) * N);  //dynamic mem allocation , because heap mem greater than stack

    for (long  i = 0; i < T; i++)
        pthread_create(&t[i], NULL, hello, (void*) i);
    

     for (long i = 0; i < T; i++)
        pthread_join(t[i], NULL);                 


    pthread_mutex_destroy(&mutex); // destroy the lock
    
    printf("Sum is : %d \n", sum+N);
    printf("Expected sum : %d \n", N*(N+1)/2);

    free(t);
    return 0;
}