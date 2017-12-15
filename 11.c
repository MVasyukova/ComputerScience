#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

int main() {

  while (true) {
    FILE * f = fopen("counter.txt", "a");
    if (f == NULL)
      continue;
    if (flock(fileno(f), LOCK_EX | LOCK_NB)) {
      printf("process %d, can't lock\n", getpid());
      continue;
    } else {
      printf("printing by %d\n", getpid());
      fprintf(f, "->%d", getpid());
      sleep(1);
      fclose(f);
      flock(fileno(f), LOCK_UN);
      sleep(1);
    }
  }

  return 0;
}
