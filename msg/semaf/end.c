#include <sys/types.h>
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
