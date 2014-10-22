#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MSG_SIZE 81
#define LAST_MESSAGE 255

int main(void) {		// Server
	int msqid, i, len, pid;
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

	/* Create or attach message queue  */
	key = ftok(pathname, 0);
	msqid = msgget(key, 0666 | IPC_CREAT);

	while (1) {
		len = sizeof(struct info);
	/* Recieve */
		msgrcv(msqid, (struct msgbuf*) &yourbuf, len, 1, 0);
		pid = yourbuf.minfo.pid;
		printf("[S]: From pid = %d: %s\n", pid, yourbuf.minfo.m);
	/* Send information */
		mybuf.mtype = yourbuf.minfo.pid;
		sprintf(mybuf.minfo.m, "OK, %d, your reques acctepted.", pid);
		mybuf.minfo.end = 0; //FIXME
		msgsnd(msqid, (struct msgbuf*) &mybuf, len, 0);
	
		if (yourbuf.minfo.end) {exit(0);}
	}

	return 0;    
}
