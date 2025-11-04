#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sched.h>

#define PIPE_NAME "/tmp/temp_pipe"
#define MAX_TEMP 90.0

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

float values[3] = {0.0, 0.0, 0.0};
volatile int idx = 0;
volatile int values_count = 0; // cuántos valores hay para promedio

// High priority thread function
void *high_priority_thread(void *arg)
{
    int pipe_fd = open(PIPE_NAME, O_RDONLY);
    if (pipe_fd == -1)
    {
        perror("Error opening pipe");
        return NULL;
    }

    float temperature;
    while (read(pipe_fd, &temperature, sizeof(float)) > 0)
    {
        if (temperature > MAX_TEMP)
        {
            printf("[HIGH] ALERT: Temperature exceeded %.1f°C: %.2f°C\n", MAX_TEMP, temperature);
            fflush(stdout);
        }
        else
        {
            pthread_mutex_lock(&mutex);
            values[idx] = temperature;
            idx = (idx + 1) % 3;
            if (values_count < 3) values_count++;
            pthread_cond_signal(&cond); // Notificar al hilo de baja prioridad
            pthread_mutex_unlock(&mutex);
        }
    }

    close(pipe_fd);
    return NULL;
}

// Low priority thread function
void *low_priority_thread(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        // Espera a que haya datos nuevos
        pthread_cond_wait(&cond, &mutex);

        // Calcular promedio solo si hay datos
        if (values_count > 0)
        {
            float sum = 0.0;
            for (int i = 0; i < values_count; i++)
                sum += values[i];
            float average = sum / values_count;
            printf("[LOW] Average of last %d temperatures: %.2f°C\n", values_count, average);
            fflush(stdout);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t high_thread, low_thread;
    pthread_attr_t attr_high, attr_low;
    struct sched_param param_high, param_low;

    // Initialize attributes for high priority thread
    pthread_attr_init(&attr_high);
    pthread_attr_setschedpolicy(&attr_high, SCHED_FIFO);
    param_high.sched_priority = sched_get_priority_max(SCHED_FIFO);
    pthread_attr_setschedparam(&attr_high, &param_high);
    pthread_attr_setinheritsched(&attr_high, PTHREAD_EXPLICIT_SCHED);

    // Initialize attributes for low priority thread
    pthread_attr_init(&attr_low);
    pthread_attr_setschedpolicy(&attr_low, SCHED_FIFO);
    param_low.sched_priority = sched_get_priority_min(SCHED_FIFO);
    pthread_attr_setschedparam(&attr_low, &param_low);
    pthread_attr_setinheritsched(&attr_low, PTHREAD_EXPLICIT_SCHED);

    // Create threads with specified attributes
    int ret;
    ret = pthread_create(&high_thread, &attr_high, high_priority_thread, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "Error creating high priority thread: %d\n", ret);
        exit(1);
    }
    ret = pthread_create(&low_thread, &attr_low, low_priority_thread, NULL);
    if (ret != 0)
    {
        fprintf(stderr, "Error creating low priority thread: %d\n", ret);
        exit(1);
    }

    pthread_join(high_thread, NULL);
    pthread_join(low_thread, NULL);

    return 0;
}
