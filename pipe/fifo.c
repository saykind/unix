#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argv, char *argc[], char *env[]) {
	char name[] = "Name.fifo";
	if (mknod(name, S_IFIFO | 0664, 0) < 0) {printf("Can\'t create FIFO\n"); exit(-1);}
	// mkfifo(name, 0664)
	
	char string[20];
	int f, fd, size;
	if((f = fork()) < 0) {printf("Can\'t fork\n"); exit(-1);}	

	if (f > 0) {
	//Parent
		fd = open(name, O_WRONLY);
		size = write(fd, "Hello, Child!", 14);
		printf("Parent: %d symbols written.\n", size);
		close(fd);
		printf("Parent: done.\n");
	}
	if (f == 0) {
	// Child
		fd = open(name, O_RDONLY);
		size = read(fd, string, 14);
		printf("Child: %d symbols read.\n", size);
		printf("Child: <%s>\n", string);
		close(fd);
		printf("Child: done.\n");
	}	
	return 0;
}
