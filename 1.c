#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main ()
{
	int fd;
	fd = open("programm.txt", O_WRONLY | O_TRUNC | O_CREAT);
	if (fd == -1) {
		perror("Ошибка");
		return -1;
	}
	
	struct stat inf;
	if  (fstat(fd, &inf) == -1) {
		perror("Ошибка stat");
		return -1; 
	}
	printf("Protection:  %03o\n", inf.st_mode & -S_IFMT);
	
	printf("size of the file: %ld bytes\n", inf.st_size);
	
	if (S_ISREG(inf.st_mode))
		printf("It is a regular file\n");
	if (S_ISDIR(inf.st_mode))
		printf("It is a directory\n");

	printf("Last change: %s", ctime(&inf.st_ctime));

	close(fd);
	return 0;
}
