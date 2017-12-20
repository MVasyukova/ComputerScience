#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main () {
	int pfd[2], PIPE = pipe(pfd);
	if (PIPE == -1)
		perror("A pipe wasn't created");
	int mfd = fcntl(pfd[1], F_SETFL, O_NONBLOCK);
	if (mfd != 0)
		perror("Flag O_NONBLOCK wasn't set");
	printf("%d %d\n", pfd[0], pfd[1]);
	char *buf = "m";
	int wr, size = 0;
	do {
		wr = write(pfd[1], buf, strlen(buf));
		size = size + wr;
	} while (wr !=-1 );
	printf("Size of pipe %d bytes\n", size+1);
	return 0;
}
