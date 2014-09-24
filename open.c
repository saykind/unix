#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LEN 100

int main(int argv, char *argc[],char *envp[]) {
	int fd = open("./test", O_RDWR | O_CREAT, 0664);	
	
	char string[] = "Hello.\n";
	int len = strlen(string);
	len++;
	
	int written = write(fd, (void *) string, len);
	fprintf(stderr, "%d/%d symblos has been written\n", written, len);
	
	char *new;
	new = (char *) malloc(LEN);
	int skip = read(fd, new, LEN); 
	fprintf(stderr, "%d/%d symblos has been read\n", skip, len);

	if(close(fd) < 0) {fprintf(stderr, "Can't close file\n");}
	return 0;
}

