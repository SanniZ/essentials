
#include "thread_fn.h"

extern pthread_mutex_t t_mutex;
extern sem_t t_sem;

void * pthread_fn(void *args)
{
	struct pthread_args *pdata = (struct pthread_args *)args;
	

        for (int i = 0; i < 10; i++) {
		//pthread_mutex_lock(&t_mutex);
		sem_wait(&t_sem);
                printf("%s sleep %d at %d loop!\n", pdata->name, pdata->sleep_time, i);
                sleep(pdata->sleep_time);
		//pthread_mutex_unlock(&t_mutex);
		sem_post(&t_sem);
        }
	printf("%s done\n", pdata->name);

	return 0;
}

