#include <pthread.h>		//compile and link with -pthread
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

long int counter = 0;

pthread_mutex_t FastMutex = PTHREAD_MUTEX_INITIALIZER;

long int ITER = 1000000;

void *sum() {
	pthread_mutex_lock(&FastMutex);
       	for(int i = 0; i < ITER; i++) {
		counter++;
	}	
	pthread_mutex_unlock(&FastMutex);
	return NULL;
}

int main()
{
	enum {
		THR_NUM = 10
	};
	pthread_t threads[THR_NUM];
	int i;
	printf("counter = %ld\n", counter);
	for (i = 0; i < THR_NUM; i++) {
		pthread_create(&threads[i], NULL, sum, NULL);
	}
	for (i = 0; i < THR_NUM; i++) {
		pthread_join(threads[i], NULL);
	}	
	printf("counter = %ld\n", counter);
	return 0;
}
