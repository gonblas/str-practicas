#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3
#define NUM_ITER 1000

void *thread_function(void *arg) {
  int id = *((int *)arg);
  for(int i = 0; i < NUM_ITER; i++) {
    printf("Thread %d: iter %d\n", id, i);
  }
  return NULL;
}


void main() {
  pthread_t threads[NUM_THREADS];

  for(int i = 0; i < NUM_THREADS; i++) {
    int *id = malloc(sizeof(int));
    *id = i;
    pthread_create(&threads[i], NULL, thread_function, id);
  }

  for(int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
}