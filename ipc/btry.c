#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int agrv, char *argc[], char *env[]) {
	
	// Generate key
	char path[] = "atry.c";
	char example = 0;
	key_t key = ftok(path, example);
	if (key < 0) {printf("Can\t generate key.\n"); exit(-1);}

	// File size
	int N = 0;
	char source[] = "atry.c";
	int fd = open(source, O_RDWR);
	N = lseek(fd, 0, SEEK_END);
	close(fd);

	// Shmget
	int err;
	int shmid = shmget(key, N*sizeof(char), 0664|IPC_CREAT|IPC_EXCL);
	err = errno;
//	printf("shmid = %d\n", shmid);
	if(shmid < 0) {
		if(err == EEXIST) {
			shmid = shmget(key, N*sizeof(char), 0);
			if (shmid < 0) {printf("Segment w that key already Can't create segment..\n"); exit(-1);}			
		} else {
			printf("Can't create segment.\n");
			exit(-1);
		}
	}

	// Attach
	char *text;
	fd = open(source, O_RDONLY);
	text = (char *)shmat(shmid, (char *) NULL, 0);
	if (text == (char *)(-1)) {printf("Can\'t attache segment.\n"); exit(-1);}

	// Action
	int i = 0;
	while (text[i] != '\0') {putchar(text[i]); i++;}


	// Detach
	if (shmdt(text) < 0) {printf("Can't detach segment"); exit(-1);}

	return 0;
}
