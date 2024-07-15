#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define NUM_THREADS 4

struct thread_data {
  int **mat1, **mat2, **result;
  int start_row, end_row;
};

void* matrix_multiply_thread(void* arg) {
  struct thread_data* data = (struct thread_data*)arg;
  int i, j, k;
  for (i = data->start_row; i < data->end_row; i++) {
    for (j = 0; j < SIZE; j++) {
      data->result[i][j] = 0;
      for (k = 0; k < SIZE; k++) {
        data->result[i][j] += data->mat1[i][k] * data->mat2[k][j];
      }
    }
  }
  return NULL;
}

int main() {
  int **mat1, **mat2, **result;
  mat1 = (int**)malloc(SIZE * sizeof(int*));
  mat2 = (int**)malloc(SIZE * sizeof(int*));
  result = (int**)malloc(SIZE * sizeof(int*));
  for (int i = 0; i < SIZE; i++) {
    mat1[i] = (int*)malloc(SIZE * sizeof(int));
    mat2[i] = (int*)malloc(SIZE * sizeof(int));
    result[i] = (int*)malloc(SIZE * sizeof(int));
  }

  // Initialize matrices mat1 and mat2
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      mat1[i][j] = i + j;
      mat2[i][j] = i * j;
    }
  }

  pthread_t threads[NUM_THREADS];
  struct thread_data data[NUM_THREADS];
  int chunk_size = SIZE / NUM_THREADS;

  for (int i = 0; i < NUM_THREADS; i++) {
    data[i].mat1 = mat1;
    data[i].mat2 = mat2;
    data[i].result = result;
    data[i].start_row = i * chunk_size;
    data[i].end_row = (i == NUM_THREADS - 1) ? SIZE : (i + 1) * chunk_size;
    pthread_create(&threads[i], NULL, matrix_multiply_thread, &data[i]);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  // Print the result matrix
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%d ", result[i][j]);
    }
    printf("\n");
  }

  // Free allocated memory
  for (int i = 0; i < SIZE; i++) {
    free(mat1[i]);
    free(mat2[i]);
    free(result[i]);
  }
  free(mat1);
  free(mat2);
  free(result);

  return 0;
}