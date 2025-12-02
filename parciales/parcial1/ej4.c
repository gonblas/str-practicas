#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

#define N_THREADS 1000

void *func_thread(void *arg)
{
	int *ret = malloc(sizeof(int)); // valor a retornar
	*ret = (rand() % 100) + 1;		// tiempo simulado
	return ret;
}


int main()
{
	pthread_t threads[N_THREADS];
	int ids[N_THREADS];
	long long suma = 0;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

	struct sched_param param;
	for (int i = 0; i < N_THREADS; i++)
	{
		ids[i] = i;

		if (i == 0) {
			param.sched_priority = 80; // alta prioridad
		}
		else {
			param.sched_priority = 10; // baja prioridad
		}
		pthread_attr_setschedparam(&attr, &param);
		pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

		pthread_create(&threads[i], &attr, func_thread, &ids[i]);
	}

	// Recolectar resultados
	int *res;
	for (int i = 0; i < N_THREADS; i++)
	{
		pthread_join(threads[i], (void **)&res);
		suma += *res;
		free(res);
	}

	double promedio = (double)suma / N_THREADS;
	printf("Promedio del tiempo de ejecucion: %.2f\n", promedio);
	pthread_attr_destroy(&attr);
	return 0;
}
