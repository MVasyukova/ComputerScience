#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main ()  {
	int fd1, fd2;							//откыли файлы	
	fd1 = open("hello.txt", O_RDONLY | O_TRUNC | O_CREAT, 0700);
	if (fd1 == -1)  {
	  perror("error in function OPEN of first file");
	  return -1;
	}
	fd2 = open("bye.txt", O_WRONLY | O_TRUNC | O_CREAT, 0700);
	if (fd2 == -1)  {
	  perror("error in function OPEN of second file");
	  return -1;
	}

	struct stat inf1, inf2;
	if (fstat(fd1, &inf1) == -1) {
	  perror("STAT error of first file");
	  return -1;
	}
	if (fstat(fd2, &inf2) == -1) {
	  perror("STAT error of second file");
	  return -1;
	}
	if ((S_ISREG(inf1.st_mode)) && (S_ISREG(inf2.st_mode)))
	  printf("Both of files are regular\n");

	char buf[1000];
	ssize_t wr, rd;
	rd = read(fd1, &buf, sizeof(buf)); 	
	if (rd == -1)  {	
	  perror("error in function READ");
	  return -1;
	}
	wr = write(fd2, &buf, rd);				
	if (wr == -1)  {	
	  perror("error in function WRITE");
	  return -1;
	} 

	close(fd1);							//закрыли
	close(fd2);
	return 0;
}
