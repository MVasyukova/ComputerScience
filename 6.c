#include <stdio.h>	
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

void listing(DIR *ptr) {
	struct dirent *list = readdir(ptr);
	int typ;
	do {
	  typ = list->d_type;
	  printf("name: %12s  type: ", list->d_name);
	  switch (typ) {
	    case 4: 
	      printf("directory\n");
	      break;
	    case 8: 
	      printf("regular file\n");
	      break;
	  }
	  if ((typ == 4) && (strcmp(list->d_name,".") !=0) && (strcmp(list->d_name,"..") !=0)) {
	    printf("\n");
	    if (opendir(list->d_name) > 0) {
	      listing(opendir(list->d_name));
	      printf("\n");
	    }
	  }
	  list = readdir(ptr);
	} while (list != NULL);
} 

int main () {
	char dir_name[] = ".";
	DIR *ptr = opendir(dir_name);
	listing(ptr);
	closedir(ptr);
	return 0;
}
