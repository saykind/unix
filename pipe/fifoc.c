#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argv, char *argc[], char *env[]) {
	char name[] = "Name.fifo";
//	if (mknod(name, S_IFIFO | 0664, 0) < 0) {printf("Can\'t create FIFO\n"); exit(-1);}
	
	char string[20];
	int f, fd, size;

	fd = open(name, O_RDONLY);
	size = read(fd, string, 14);
	printf("Child: %d symbols read.\n", size);
	printf("Child: <%s>\n", string);
	close(fd);
	printf("Child: done.\n");
	return 0;
}
