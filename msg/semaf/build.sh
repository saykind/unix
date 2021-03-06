semaf/end.c                                                                                         0000664 0001750 0001750 00000001523 12424133461 012754  0                                                                                                    ustar   saykind                         saykind                                                                                                                                                                                                                #include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MSG_SIZE 81
#define SoB sizeof(struct minfo)

int main(int argc, char *argv[], char *envp[]) {
	int msqid;
	long pid;
	char pathname[] = "FILE";
	key_t  key;
	struct mymsgbuf {
		long mtype;
		struct minfo {
			long pid;
			short op;
			int num;
			char m[MSG_SIZE];
			int init;
			int end;
		} info;
	} mybuf, yourbuf;

	key = ftok(pathname, 0);
	msqid = msgget(key, 0666 | IPC_CREAT);
	printf("[C]: msqid = %d\n", msqid);


	pid = getpid();
	mybuf.mtype = 1;
    	mybuf.info.pid = pid;
	mybuf.info.op  = 1;
	mybuf.info.num = 0;
	mybuf.info.end = 1;
	msgsnd(msqid, (struct msgbuf*) &mybuf, SoB, 0);
	msgrcv(msqid, (struct msgbuf*) &yourbuf, SoB, pid, 0);
	printf("[C]: From [S]: %s\n", yourbuf.info.m);

	return 0;
}
                                                                                                                                                                             semaf/FILE                                                                                          0000664 0001750 0001750 00000000000 12424132550 012467  0                                                                                                    ustar   saykind                         saykind                                                                                                                                                                                                                semaf/minus.c                                                                                       0000664 0001750 0001750 00000001524 12424133446 013345  0                                                                                                    ustar   saykind                         saykind                                                                                                                                                                                                                #include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MSG_SIZE 81
#define SoB sizeof(struct minfo)

int main(int argc, char *argv[], char *envp[]) {
	int msqid;
	long pid;
	char pathname[] = "FILE";
	key_t  key;
	struct mymsgbuf {
		long mtype;
		struct minfo {
			long pid;
			short op;
			int num;
			char m[MSG_SIZE];
			int init;
			int end;
		} info;
	} mybuf, yourbuf;

	key = ftok(pathname, 0);
	msqid = msgget(key, 0666 | IPC_CREAT);
	printf("[C]: msqid = %d\n", msqid);


	pid = getpid();
	mybuf.mtype = 1;
    	mybuf.info.pid = pid;
	mybuf.info.op  = -1;
	mybuf.info.num = 0;
	mybuf.info.end = 0;
	msgsnd(msqid, (struct msgbuf*) &mybuf, SoB, 0);
	msgrcv(msqid, (struct msgbuf*) &yourbuf, SoB, pid, 0);
	printf("[C]: From [S]: %s\n", yourbuf.info.m);

	return 0;
}
                                                                                                                                                                            semaf/plus.c                                                                                        0000664 0001750 0001750 00000001523 12424133437 013174  0                                                                                                    ustar   saykind                         saykind                                                                                                                                                                                                                #include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MSG_SIZE 81
#define SoB sizeof(struct minfo)

int main(int argc, char *argv[], char *envp[]) {
	int msqid;
	long pid;
	char pathname[] = "FILE";
	key_t  key;
	struct mymsgbuf {
		long mtype;
		struct minfo {
			long pid;
			short op;
			int num;
			char m[MSG_SIZE];
			int init;
			int end;
		} info;
	} mybuf, yourbuf;

	key = ftok(pathname, 0);
	msqid = msgget(key, 0666 | IPC_CREAT);
	printf("[C]: msqid = %d\n", msqid);


	pid = getpid();
	mybuf.mtype = 1;
    	mybuf.info.pid = pid;
	mybuf.info.op  = 1;
	mybuf.info.num = 0;
	mybuf.info.end = 0;
	msgsnd(msqid, (struct msgbuf*) &mybuf, SoB, 0);
	msgrcv(msqid, (struct msgbuf*) &yourbuf, SoB, pid, 0);
	printf("[C]: From [S]: %s\n", yourbuf.info.m);

	return 0;
}
                                                                                                                                                                             semaf/server.c                                                                                      0000664 0001750 0001750 00000005026 12426230576 013525  0                                                                                                    ustar   saykind                         saykind                                                                                                                                                                                                                #include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define NoP 4
#define NoS 10
#define MSG_SIZE 81
#define SoB sizeof(struct minfo)

/* FIFO array of longs */
int amount = 0;
long *init(int N) {
	long *fifo = (long *) malloc(N*sizeof(long));
	int i;
	for (i = 0; i < N; i++) {fifo[i] = 0;}
	return fifo;
};
void push(long *fifo, int N, long new) {
	fifo[amount++] = new;
	return;
}
long pop(long *fifo, int N) {
	long ret = fifo[0];
	int i;
	for (i = 0; i < N-1; i++)
		fifo[i] = fifo[i+1];
	amount--;
	return ret;
}


int main(void) {
	int msqid, i, num ,op;
	long pid;
	char pathname[] = "FILE";
	key_t  key;
	struct mymsgbuf {
		long mtype;
		struct minfo {
			long pid;
			short op;
			int num;
			char m[MSG_SIZE];
			int init;
			int end;
		} info;
	} mybuf, yourbuf;

	/* Create or attach message queue  */
	key = ftok(pathname, 0);
	msqid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
	if ((msqid < 0) && (errno == EEXIST)) {
		printf("[S]: EEXIST\n");
		msqid = msgget(key, 0666 | IPC_CREAT);
	       	//return 0;
	}
	
	/* FIFO array */
	long *fifo = init(NoP);
	int S0 = 0;

	printf("[S]: msqid = %d\n\n", msqid);
	while (1) {
		/* Recieve */
		msgrcv(msqid, (struct msgbuf *) &yourbuf, SoB, 1, 0);
		pid = yourbuf.info.pid;
		num = yourbuf.info.num;
		op = yourbuf.info.op;
		printf("[S]: Recived message from pid = %ld, op = %d\n", pid, op);
		if (op == 1) {
			S0++;
			/* Send information */
			mybuf.mtype = pid;
			mybuf.info.pid = 1;
			sprintf(mybuf.info.m, "OK, %ld, V-action complited.", pid);
			msgsnd(msqid, (struct msgbuf *) &mybuf, SoB, 0);
			printf("[S]: Sended message to %ld\n", pid);
			if (amount > 0) {
			//if (fifo[0] != 0) {
				S0--;
				pid = pop(fifo, NoP);
				printf("[S]: Poped from FIFO %ld\n", pid);
				// Send information
				mybuf.mtype = pid;
				mybuf.info.pid = 1;
				sprintf(mybuf.info.m, "OK, %ld, P-action complited.", pid);
				msgsnd(msqid, (struct msgbuf *) &mybuf, SoB, 0);
				printf("[S]: Sended message to %ld\n", pid);
			}
		}
		if (op == -1) {
			if (S0 < 1) {
				push(fifo, NoP, pid);
				printf("[S]: Push %ld to FIFO\n", pid);
			}
			else {
				S0--;
				// Send information
				mybuf.mtype = pid;
				mybuf.info.pid = 1;
				sprintf(mybuf.info.m, "OK, %ld, P-action complited.", pid);
				msgsnd(msqid, (struct msgbuf *) &mybuf, SoB, 0);
				printf("[S]: Sended message to %ld\n", pid);
			}
		}
		printf("[S]: S0 = %d\tIn FIFO = %d\n\n", S0, amount);
		if (yourbuf.info.end) {exit(0);}
	}

	free(fifo);
	return 0;    
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          