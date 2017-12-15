#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>

int main () {
	printf("main process started: %d\n", getpid());
	long page_size = sysconf(_SC_PAGESIZE);
	void *buffer = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (buffer == MAP_FAILED) {
		perror("mmap failed");
		return 1;
	}
	char *s = buffer;
	strcpy(s, "Hello");
	puts(s);
	pid_t ch = fork();
	if(ch == -1) {
		perror("");
		return 1;
	}
	if (ch == 0) {
		printf("%d %s\n", getpid(), s);
		strcpy(s, "Child was here");
		printf("%d %s\n", getpid(), s);
		return 0;
	}
	wait(NULL);
	puts(s);
	return 0;
}
