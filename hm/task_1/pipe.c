/* David Saykin
** Group 323
** I've just modified last task. 
** Parent says 'Hello, child!' to pipe buffer child read this and answers.
** file descripts are given by arguments.
** Use run.sh to compile both files and run the programm. 
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int fd[2], FD[2], result;
	size_t size, SIZE;
	char  resstring[14], RESstring[15];

	if(pipe(fd) < 0){
		printf("Can\'t open pipe\n");
		exit(-1);
	}
	if(pipe(FD) < 0){
     		printf("Can\'t open pipe\n");
     		exit(-1);
   	}

	result = fork();

	if(result < 0) {
		printf("Can\'t fork child\n");
		exit(-1);
	} 
	if (result > 0) {/* Parent process */
		close(fd[0]);
      		size = write(fd[1], "Hello, child!", 14);
      		if(size != 14){
        		printf("Can\'t write all string to pipe\n");
        		exit(-1);
      		}
      		close(fd[1]);

      		close(FD[1]);
      		SIZE = read(FD[0], RESstring, 15);
      		if(SIZE < 0){
         		printf("Can\'t read string from pipe\n");
         		exit(-1);
      		}
      		close(FD[0]);

      		printf("Parent've got the message: <%s>\n", RESstring);
	}
	if (result == 0) {/* Child process */

		char arg1[10], arg2[10], arg3[10], arg4[10];
		sprintf(arg1, "%d", fd[0]);
		sprintf(arg2, "%d", fd[1]);
		sprintf(arg3, "%d", FD[0]);
		sprintf(arg4, "%d", FD[1]);
		execlp("./bin","./bin", arg1, arg2, arg3, arg4, (char *)NULL);
		exit(-1);		
/*		close(fd[1]);
      		size = read(fd[0], resstring, 14);
      		if(size < 0){
         		printf("Can\'t read string from pipe\n");
         		exit(-1);
      		}
      		close(fd[0]);

      		close(FD[0]);
      		SIZE = write(FD[1], "Hello, parent!", 15);
      		if(SIZE != 15){
        		printf("Can\'t write all string to pipe\n");
        		exit(-1);
      		}
      		close(FD[1]);

      		printf("Child exit, result: %s\n", resstring);
*/   	}	
   	return 0;
}
