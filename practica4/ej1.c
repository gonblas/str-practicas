#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <linux/time.h>

#define THREAD_COUNT 2
#define ITERATIONS 1000
#define PERIOD_NS 10000000 // 10 ms (100 Hz) in ns
#define NSEC_PER_SEC 1000000000L

void sleep_until(struct timespec *next_release, long delay_ns) {
    next_release->tv_nsec += delay_ns;
    while (next_release->tv_nsec >= NSEC_PER_SEC) {
        next_release->tv_nsec -= NSEC_PER_SEC;
        next_release->tv_sec++;
    }
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, next_release, NULL);
}

void *thread_function(void *arg)
{
    struct timespec next_release, now;
    long long latency_sum = 0;
    int thread_id = *(int *)arg;
    free(arg);

    // Initialize the first release time
    clock_gettime(CLOCK_MONOTONIC, &next_release);

    for (int i = 0; i < ITERATIONS; i++)
    {
        sleep_until(&next_release, PERIOD_NS);
        clock_gettime(CLOCK_MONOTONIC, &now);
        long long latency = (now.tv_sec - next_release.tv_sec) * NSEC_PER_SEC +
                            (now.tv_nsec - next_release.tv_nsec);
        if (latency > 0)
            latency_sum += latency;
    }

    // Compute average latency in microseconds
    double avg_latency_us = (double)latency_sum / (ITERATIONS * 1000.0);
    printf("Thread %d average latency: %.2f us\n", thread_id, avg_latency_us);

    return NULL;
}

int main()
{
    pthread_t threads[THREAD_COUNT];

    // Create threads
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        int *thread_id = malloc(sizeof(int));
        if (!thread_id)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        *thread_id = i + 1;

        int r = pthread_create(&threads[i], NULL, thread_function, thread_id);
        if (r != 0)
        {
            fprintf(stderr, "Failed to create thread %d\n", i + 1);
            free(thread_id);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
