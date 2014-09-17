#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
	
	execle("/bin/cat", "/bin/cat", "exec.c", (char *)NULL, envp);
	
	printf("Error on program start\n");
    	exit(-1);
	return 0;
}

