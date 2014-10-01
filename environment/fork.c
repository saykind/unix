#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	pid_t pid, ppid, forkval;
	forkval = fork();
	pid = getpid();
	ppid = getppid();
	switch(forkval) {
		case -1:
			perror("fork");
			break;
		case 0:
//			execl("/bin/echo","/bin/echo","I was born by child", (char *)NULL);
			printf("I'm child\n");
			printf("PID = %d\n", pid);
			printf("PPID = %d\n\n", ppid);
			break;
		default:
			printf("I'm parent\n");
			printf("PID = %d\n", pid);
			printf("PPID = %d\n\n", ppid);
			break;
	}
	return 0;
}
