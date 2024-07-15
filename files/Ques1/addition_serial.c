#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10000

void *hello(void *arg) {
    int *arr1 = (int *)arg;
    int *arr2 = arr1 + N;
    int *arr3 = arr2 + N;

    for (int i = 0; i < N; i++) {
        arr3[i] = arr1[i] + arr2[i];
    }

    return NULL;
}

int main() {
    int *arr = (int *)malloc(sizeof(int) * 3 * N);

    int *arr1 = arr;
    int *arr2 = arr1 + N;
    int *arr3 = arr2 + N;

    for (int i = 0; i < N; i++) {
        arr1[i] = i + 1;
        arr2[i] = i + 1;
    }

    pthread_t thread;
    pthread_create(&thread, NULL, hello, arr);
    pthread_join(thread, NULL);

    for(int i = 0; i < N; i++){
        printf("%d ",arr3[i]);
    }

    free(arr);

    return 0;
}