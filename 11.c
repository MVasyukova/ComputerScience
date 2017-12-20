#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

int main() {
	FILE * f = fopen("counter.txt", "r+");
	if (f == NULL) {
		perror("File to write wasn't opened");
		return 1;
	}
	if (flock(fileno(f), LOCK_EX) == -1) {
		perror("Flock\n");
		fclose(f);
		return 1;
	}
	else {
		printf("printing by %d\n", getpid());
		int number;
		if (fscanf(f, "%d", &number) != 1) 
			number = 0;
		else number++;
		rewind(f);
		printf("%d\n", number);
		fprintf(f, "%d", number);
		flock(fileno(f), LOCK_UN);
		fclose(f);
	}
	return 0;
}
