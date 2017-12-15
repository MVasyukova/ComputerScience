#include <pthread.h>		//compile and link with -pthread
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

long int ITER = 1000000;

void *sum(void *args) {
	int *buf = args;
	for (int j = 0; j < ITER; j ++) {
		(*buf) ++;
	}
	return NULL;
}

int main()
{
	enum {
		THR_NUM = 10
	};
	long int counter = 0;
	long int buf[THR_NUM];
	pthread_t threads[THR_NUM];
	int i;
	printf("counter = %ld\n", counter);
	for (i = 0; i < THR_NUM; i++) {
		buf[i] =  0;
		pthread_create(&threads[i], NULL, sum, &buf[i]);
	}
	for (i = 0; i < THR_NUM; i++) {
		pthread_join(threads[i], NULL);
	}
	for (i = 0; i < THR_NUM; i++) {
		counter += buf[i];
	}
	printf("counter = %ld\n", counter);	
	return 0;
}
