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

int main(int argv, char *argc[], char *envp[]){
		int fd[2], FD[2];
		fd[0] = atoi(argc[1]);
		fd[1] = atoi(argc[2]);
		FD[0] = atoi(argc[3]);
		FD[1] = atoi(argc[4]);

		char resstring[14], RESstring[15];		
		close(fd[1]);
      		int size = read(fd[0], resstring, 14);
      		if(size < 0){
         		printf("Can\'t read string from pipe\n");
         		exit(-1);
      		}
      		close(fd[0]);

      		close(FD[0]);
      		int SIZE = write(FD[1], "Hello, parent!", 15);
      		if(SIZE != 15){
        		printf("Can\'t write all string to pipe\n");
        		exit(-1);
      		}
      		close(FD[1]);

      		printf("Child've got the message: <%s>\n", resstring);
  		
   	return 0;
}
