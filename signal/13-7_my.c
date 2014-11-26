#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

int terminated = 10;

void reaction(int nsig){
	int status;
	pid_t pid;
	if((pid = waitpid(-1, &status, 0))  > 0) {
		if ((status & 0xff) == 0) {
			printf("Process %d was exited with status %d\n", pid, status >> 8);
			terminated--;
		} else if ((status & 0xff00) == 0){
			printf("Process %d killed by signal %d %s\n", pid, status &0x7f,
			(status & 0x80) ? "with core file" : "without core file");
		}
	reaction(nsig);
	}
}

int main(void){
	pid_t pid;
	int i,j;
	signal(SIGCHLD, reaction);
	
	for(i=0; i<10; i++){
		pid = fork();
		if (pid == 0){
			/* Child  */
			exit(i+1);
		}
	}
	
	while(terminated);
	
	return 0;
}
