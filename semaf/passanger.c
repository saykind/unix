#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define N 4
#define M 12

int main(int argc, char *argv[], char *envp[])
{
	int	f[M];
	int	i, err;
	int	semid;
	char	pathname[]="file";
	key_t	key;
	struct sembuf	*buf1, *buf2, *buf3;
	buf1 = (struct sembuf *) malloc(sizeof(struct sembuf));
	buf2 = (struct sembuf *) malloc(sizeof(struct sembuf));
	buf3 = (struct sembuf *) malloc(sizeof(struct sembuf));
    
	key = ftok(pathname, 0);
    	semid = semget(key, 3, 0666 | IPC_CREAT);
	if (semid < 0) {printf("Can\'t create semaphore set\n");exit(-1);}


	for (i = 0; i < M; i++) 
		f[i] = -1;
	for (i = 0; i < M; i++) { 
		f[i] = fork();
		if (f[i] == 0) {
			//printf("[%d] I'm born.\n", i );
			break;
		}
	}
	
	for (i = 0; i < M; i++) {
		if (f[i] == 0) {
			buf1->sem_num = 0;
			buf1->sem_op  = -1;
			buf1->sem_flg = 0;
			semop(semid, buf1, 1);
			printf("[%d]: Found vacant place.\n", i);

			buf2->sem_num = 1;
			buf2->sem_op  = 1;
			buf2->sem_flg = 0;
			semop(semid, buf2, 1);
			printf("[%d]: Sat in boat.\n", i);
			
			buf3->sem_num = 2;
			buf3->sem_op  = -1;
			buf3->sem_flg = 0;
			semop(semid, buf3, 1);
			printf("[%d]: Made a cruis.\n", i);
			}
	}

	free(buf1);
	free(buf2);	
	free(buf3);
	return 0;
}
