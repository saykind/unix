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
	int	i, j, err;
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


	buf1->sem_num = 0;
	buf1->sem_op  = N;
	buf1->sem_flg = 0;
	semop(semid, buf1, 1);
	printf("[B]: There ia %d vacant places\n", N);

	j = M; 
	while (j) {
		buf1->sem_num = 0;
		buf1->sem_op  = 0;
		buf1->sem_flg = 0;
		semop(semid, buf1, 1);
		printf("[B]: I'm full.\n", i);

		buf2->sem_num = 1;
		buf2->sem_op  = -N;
		buf2->sem_flg = 0;
		semop(semid, buf2, 1);
		printf("[B]: Have %d people on bort.\n", N);
		printf("[B]: Out on cruise.\n", N);
		sleep(3); printf("Out...\n");
		sleep(3); printf("Out...\n");
		
		printf("[B]: Made a cruis.\n");
		buf3->sem_num = 2;
		buf3->sem_op  = N;
		buf3->sem_flg = 0;
		semop(semid, buf3, 1);
		printf("[B]: Said everybody that cruis is made.\n", N);
		
		buf3->sem_num = 2;
		buf3->sem_op  = 0;
		buf3->sem_flg = 0;
		semop(semid, buf3, 1);
		printf("[B]: Everybody knows that he made a cruis.\n");

		buf1->sem_num = 0;
		buf1->sem_op  = N;
		buf1->sem_flg = 0;
		semop(semid, buf1, 1);
		if (j > 4) printf("[B]: You're welcome.\n");
		j -= N;	

	}

	free(buf1);
	free(buf2);	
	free(buf3);
	return 0;
}
