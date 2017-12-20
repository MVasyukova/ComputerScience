#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	DIR * D = opendir(argv[1]);
	DIR * ND = opendir(argv[2]);
	if (ND == NULL)
	    mkdir(argv[2], 0777);
	closedir(ND);

	for (struct dirent *DE = readdir(D); DE != NULL; DE = readdir(D)) {
		printf("%s, %d\n", DE->d_name, DE->d_type);
		if (strcmp(DE->d_name, ".") == 0 || strcmp(DE->d_name, "..") == 0) continue;
    		if (DE->d_type == DT_DIR) {
			char * name_in = (char *)malloc(strlen(argv[1])+1+strlen(DE->d_name)+1);
			char * name_out = (char *)malloc(strlen(argv[2])+1+strlen(DE->d_name)+1);
			if ((name_in == NULL) || (name_out == NULL)) {
				perror("Memory wasn't allocated");
				break;
			}
			strcpy(name_in, argv[1]);
			strcat(name_in, "/");
			strcat(name_in, DE->d_name);
			strcpy(name_out, argv[2]);
			strcat(name_out, "/");
			strcat(name_out, DE->d_name);
			printf("%s, %s\n", name_in, name_out);
			int fd_in = open(name_in, O_RDONLY);
			int fd_out = open(name_out, O_WRONLY | O_CREAT);
			char buf[1024];
			int count;
			while ((count = read(fd_in, buf, sizeof(buf))) > 0)
				write(fd_out, buf, count);
			free(name_in);
			free(name_out);
			close(fd_in);
			close(fd_out);
		}
	}
	closedir(D);
	return 0;
}


