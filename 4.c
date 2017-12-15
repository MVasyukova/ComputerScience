#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
  int fd_in = open("in.txt", O_RDONLY, 0700);
  int fd_out = open("out.txt", O_WRONLY | O_CREAT, 0700);
  char buf[20];
  size_t buf_size;
  off_t offset = 0;
  do {
    buf_size = pread(fd_in, buf, sizeof(buf), offset);
    pwrite(fd_out, buf, buf_size, offset);
    offset = lseek(fd_out, 0L, SEEK_END);
  } while (buf_size > 0);
  close(fd_in);
  close(fd_out);
  return 0;
}


