#include <pthread.h>		//compile and link with -pthread
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdatomic.h>

long int counter = 0;

long int ITER = 1000000;

void *sum() {
	for (int j = 0; j < ITER; j ++) {
		atomic_fetch_add(&counter, 1);		
	}
	return NULL;
}

int main()
{
	enum {
		THR_NUM = 10
	};
	pthread_t threads[10];
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
