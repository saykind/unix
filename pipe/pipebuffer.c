// carpson@mail.ru
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int fd[2], i, j, result, LEN = 65530;
	int f[100000];
	size_t size;
	char string[LEN];

	for (LEN = 65530; ; LEN++) {
		f[LEN] = fork();
		if (f[LEN] == 0) {
			if (pipe(fd) < 0) {printf("Can\'t open pipe\n");exit(-1);}
			size = write(fd[1], string, LEN);
			if (size != LEN) {printf("Can\'t write all string to pipe\n");exit(-1);}
      			close(fd[1]);
			printf("%d\n", LEN);
			exit(0);
		}
	}
      	close(fd[1]);
   	return 0;
}
