#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

#define sigzero SIGUSR1 
#define sigone  SIGUSR2
#define sigready SIGQUIT

char yready = 1;
pid_t ypid = 0;
int recvNumber = 0;
char recvCounter = 0;

void setready(int sig) {
	yready = 1;
}

void reaction(int sig) {
	if (sig == sigzero) {recvCounter++; /*printf("Received 0\n");*/}
	if (sig == sigone) {recvNumber += 1<<recvCounter; recvCounter++; /*printf("Received 1\n");*/}
	kill(ypid, sigready); 
}

int main(void) {
	signal(sigzero, reaction);
	signal(sigone,  reaction);
	signal(sigready, setready);
	
	pid_t mpid = getpid();
	printf("Sender\n");
	printf("%d\n", mpid);
	scanf("%d", &ypid);
	
	/* main body */
	int sentNumber = 0, i = 0;
	sentNumber = 400;
	while ((i++ < 8*sizeof(int)) & (yready)) {
		if ((sentNumber>>(i-1))&(0x1)) {	
			kill(ypid, sigone);
			//printf("Sended 1\n");
		} else {
			kill(ypid, sigzero);
			//printf("Sended 0\n");
		}
		yready = 0;
		while (!yready);
	} 
	printf("Sended: %d\n", sentNumber);
	/* main body */
	return 0;
}

