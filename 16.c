#include <fcntl.h>    //Link with -lrt
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>

int main () {
	mqd_t Que = mq_open("/message", O_RDWR | O_CREAT);
	if (Que == -1)
		perror("Message queue wasn't created");
	
	struct mq_attr charac;
	int ch = mq_getattr(Que, &charac);
	if (ch == -1)
		perror("Error of mq_getattr");
	printf("Max number of messages in a queue: %ld \n", charac.mq_maxmsg);
	printf("Max size of message: %ld bytes\n", charac.mq_msgsize);
	printf("Current number of messages: %ld\n", charac.mq_curmsgs);

	mq_close(Que);
	int linking  = mq_unlink("/message");
	return 0;
}
