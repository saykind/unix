#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argv, char *argc[], char *env[]) {
	char name[] = "Name.fifo";
	if (mknod(name, S_IFIFO | 0664, 0) < 0) {printf("Can\'t create FIFO\n"); exit(-1);}
	
	char string[20];
	int  fd, size;

	if((fd = open(name, O_WRONLY)) < 0) {exit(-1);};
	printf("Parent: fd = %d\n", fd);
	size = write(fd, "Hello, Child!", 14);
	printf("Parent: %d symbols written.\n", size);
	close(fd);
	printf("Parent: done.\n");
	return 0;
}
