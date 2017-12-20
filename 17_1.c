#include <fcntl.h>		//Link with -lrt
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	mqd_t Que = mq_open(argv[argc - 2], O_WRONLY);
	if (Que == -1) {
		perror("Message queue wasn't open");
		return -1;
	}
	
	struct mq_attr charac;
	int ch = mq_getattr(Que, &charac);
	if (ch == -1)
		perror("Error of mq_getattr");

	ssize_t push;
	unsigned int an_prio = 1;
	push = mq_send(Que, argv[3], strlen(argv[3]), an_prio);
	if (push == -1) {
		perror("The message wasn't written");
	}
	mq_close(Que);
	return 0;
}	
