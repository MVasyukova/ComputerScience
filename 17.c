#include <fcntl.h>    //Link with -lrt
#include <sys/stat.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

int main () {
	mqd_t Que = mq_open("/MessageTable", O_RDWR | O_CREAT);
	if (Que == -1)
	  perror("Message queue wasn't created");
	
	struct mq_attr charac;
	int ch = mq_getattr(Que, &charac);
	if (ch == -1)
	  perror("Error of mq_getattr");

	ssize_t push;
	char *an_buf = "Hello!";	
	unsigned int an_prio = 1;
	int i = 0;
	for (i; i < 2; i++) {
	  push = mq_send(Que, an_buf, strlen(an_buf), an_prio);
	}
	if (push == -1)
	  perror("The message wasn't written");
	
	printf("Number of messages: %ld\n", charac.mq_curmsgs);	

	ssize_t pop;
	char buf[1024];	
	unsigned int *prio;
	if (charac.mq_curmsgs == 0) 
	  printf("Queue is empty\n");
	for (i = 0; i < 3; i++) {
	    pop = mq_receive(Que, buf, charac.mq_msgsize, prio);
	    printf("Message: %s\n", buf);
	    if (pop == -1) {
	      perror("Queue couldn't be readed");
	    }
	}

	mq_close(Que);
	int linking  = mq_unlink("/MessageTable");
	return 0;
}
