#include <pthread.h>		//compile and link with -pthread
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

long int counter = 0;

long int ITER = 1000000;

sem_t * semaphore;

void *sum() {
	sem_wait(semaphore);
	for (int i = 0; i < ITER; i++) {
		counter++;
	}
	sem_post(semaphore);
	return NULL;
}

int main()
{
	enum {
		THR_NUM = 10
	};
	pthread_t threads[THR_NUM];
	int i;
	semaphore = sem_open("Semaphore", O_CREAT, 0777, 1); 
	printf("counter = %ld\n", counter);
	for (i = 0; i < THR_NUM; i++) {
		pthread_create(&threads[i], NULL, sum, NULL);
	}
	for (i = 0; i < THR_NUM; i++) {
		pthread_join(threads[i], NULL);
	}	
	sem_close(semaphore);
	sem_unlink("Semaphore");
	printf("counter = %ld\n", counter);
	return 0;
}
