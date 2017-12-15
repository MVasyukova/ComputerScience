#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main ()  {
	int fd = open("hello.txt", O_WRONLY | O_TRUNC | O_CREAT, 0700);
	if (fd == -1)  {
	  perror("error in function OPEN");
	  return -1;
	}
	char *buf="Мой дядя самых честный правил.\n Когда не в шутку занемог,\n Он уважать себя заставил\n И лучше выдумать не мог!\n";
	ssize_t wr=write(fd, buf, strlen(buf));
	if (wr == -1)  {
	  perror("error in function WRITE");
	  return 0;
	}
	printf("%ld\n", wr);
	close(fd);
	return 0;
}
