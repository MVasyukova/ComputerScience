#include <pthread.h> //compile and link with -pthread
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

void* thr_worker(void * argu)
{
	uint64_t *p = argu;
	while (1) {
	  (*p)++;
	}
	return NULL;
}

int main () {
	uint64_t i = 0;
	pthread_t worker;
	if (errno = pthread_create(&worker, NULL, thr_worker, &i)) {
	  perror("Thread couldn't be created");
	}
	int j;
	for (j = 0; j < 10; j++) {
	  sleep (1);
//	  unsigned long long m =  (unsigned long long)i;
	  printf("i = %llu\n", (unsigned long long)i);
	}
	pthread_kill(worker,SIGINT);
	return 0;
}
