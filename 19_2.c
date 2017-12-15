#include <pthread.h>		//compile and link with -pthread
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <semaphore.h>

long int counter = 0;

long int ITER = 1000000;    

sem_t semaphore;

void *sum() {
	sem_wait(&semaphore);
	for (int i = 0; i < ITER; i++) {
		counter++;
	}
	sem_post(&semaphore);
	return NULL;
}

int main()
{
	enum {
		THR_NUM = 10
	};
	pthread_t threads[THR_NUM];
	sem_init(&semaphore, 0, 1);
	int i;
	printf("counter = %ld\n", counter);
	for (i = 0; i < THR_NUM; i++) {
		pthread_create(&threads[i], NULL, sum, NULL);
	}
	for (i = 0; i < THR_NUM; i++) {
		pthread_join(threads[i], NULL);
	}	
	sem_destroy(&semaphore);
	printf("counter = %ld\n", counter);
	return 0;
}
