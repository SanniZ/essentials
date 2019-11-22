#ifndef __THREAD_FN_H__
#define __THREAD_FN_H__

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

struct pthread_args{
    char name[16];
    int sleep_time;
};

void * pthread_fn(void *args);

#endif
