#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <utime.h>
#include <time.h>

int main() {
  int fd_in = open("in.txt", O_RDONLY, 0700);
  int fd_out = open("out.txt", O_WRONLY | O_CREAT, 0700);
  char buf[256];
  printf("size --- %ld\n", sizeof(buf));
  size_t buf_size;
  do {
    buf_size = read(fd_in, buf, sizeof(buf));
    printf("%ld\n", buf_size);
    write(fd_out, buf, buf_size);
  } while (buf_size > 0);
  struct stat st_buf;
  struct timespec ts_buf[2];
  fstat(fd_in, &st_buf);
  ts_buf[0] = st_buf.st_atim;
  ts_buf[1] = st_buf.st_mtim;
  futimens(fd_out, ts_buf);
  close(fd_in);
  close(fd_out);
  return 0;
}


