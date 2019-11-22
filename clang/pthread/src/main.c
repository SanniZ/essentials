#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "thread_fn.h"

#define THREADS_MAX  3

pthread_mutex_t t_mutex;
sem_t t_sem;

int main(int argc, char **argv)
{
	pthread_t tid[THREADS_MAX];
	struct pthread_args args[THREADS_MAX];

	pthread_mutex_init(&t_mutex, NULL);
	sem_init(&t_sem, 0, 2);

	for (int i = 0; i < THREADS_MAX; i++) {
		args[i].sleep_time = (i + 1) * (i + 1);
		sprintf(args[i].name, "pthead_%d", i);
		pthread_create(&tid[i], NULL, pthread_fn, (void *)&args[i]);
	}

	for (int i = 0; i < THREADS_MAX; i++) {
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&t_mutex);
	sem_destroy(&t_sem);
      
	return 0;
}
