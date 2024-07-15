#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<pthread.h>

#define N 100000
#define NUM_THREADS 4

struct thread_data {
  int start, end, count;
};

void* count_primes(void* arg) {
  struct thread_data* data = (struct thread_data*)arg;
  int i, j;
  int flag;
  
  for(i=data->start;i<data->end;i++)
  {
    flag = 0;
    for(j=2;j<i;j++)    
    {
      if((i%j) == 0)
      {
        flag = 1;
        break;
      }
    }
    if(flag == 0)
    {
      data->count++;
    }
  }
  
  return NULL;
}

int main()
{
  int i;
  int count = 0;
  struct thread_data data[NUM_THREADS];
  pthread_t threads[NUM_THREADS];
  int chunk_size = N / NUM_THREADS;
  double exe_time;
  struct timeval start_time, stop_time;
  
  gettimeofday(&start_time, NULL);
  
  for(i=0;i<NUM_THREADS;i++)
  {
    data[i].start = i * chunk_size + 1;
    data[i].end = (i == NUM_THREADS - 1) ? N : (i + 1) * chunk_size;
    data[i].count = 0;
    pthread_create(&threads[i], NULL, count_primes, &data[i]);
  }
  
  for(i=0;i<NUM_THREADS;i++)
  {
    pthread_join(threads[i], NULL);
    count += data[i].count;
  }
  
  gettimeofday(&stop_time, NULL);  
  exe_time = (stop_time.tv_sec+(stop_time.tv_usec/1000000.0)) - (start_time.tv_sec+(start_time.tv_usec/1000000.0));
  
  printf("\n Number of prime numbers = %d \n Execution time is = %lf seconds\n", count+1, exe_time);
  
  return 0;
}