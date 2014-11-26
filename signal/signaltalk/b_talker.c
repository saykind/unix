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
	printf("Reciever\n");
	printf("%d\n", mpid);
	scanf("%d", &ypid);

	/* main body */	
	while(recvCounter < 8*sizeof(int)) {}
	printf("Received: %d\n", recvNumber); 
	/* main body */

	return 0;
}

