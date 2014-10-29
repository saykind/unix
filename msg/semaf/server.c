#include <sys/types.h>
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
		printf("EEXIST\n");
		msqid = msgget(key, 0666 | IPC_CREAT);
	       	//return 0;
	}
	
	/* FIFO array */
	long *fifo = init(NoP);
	int S0 = 0;

	printf("[S]: msqid = %d\n", msqid);
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
			if (fifo[0] != 0) {
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
		printf("\n");
		if (yourbuf.info.end) {exit(0);}
	}

	free(fifo);
	return 0;    
}
