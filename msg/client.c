#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MSG_SIZE 81
#define LAST_MESSAGE 255

int main(void) {
	int msqid, len, pid = getpid();
	char pathname[]="FILE";
	key_t  key;
	struct mymsgbuf {
		long mtype;
		struct info {
			int pid;
			char m[MSG_SIZE];
			short end;
		} minfo;
	} mybuf, yourbuf;

	/* Create message queue */
	key = ftok(pathname, 0);
	msqid = msgget(key, 0666 | IPC_CREAT);


	len = sizeof(struct info);
	/* Send information */
	mybuf.mtype = 1;
	mybuf.minfo.pid = pid;
	mybuf.minfo.end = 0;
	sprintf((mybuf.minfo).m, "Request from %d", pid);
	msgsnd(msqid, (struct msgbuf*) &mybuf, len, 0);
	/* Recieve */
	msgrcv(msqid, (struct msgbuf*) &yourbuf, len, pid, 0);
	printf("[%d] From server: %s\n", pid, yourbuf.minfo.m);
	if (yourbuf.minfo.end) {exit(0);}

	return 0;       
}
