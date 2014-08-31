#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	pid_t pid, ppid;
	pid = getpid();
	ppid = getppid();

	printf("PID = %d\tPPID = %d\n", pid, ppid);
	return 0;
}
