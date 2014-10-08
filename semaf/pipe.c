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
		int   semid;
		char pathname[]="08-1a.c";
		key_t key;
		struct sembuf mybuf;
		key = ftok(pathname, 0);
		if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){
			printf("Can\'t create semaphore set\n");
			exit(-1);
 		}
		mybuf.sem_num = 0;
		mybuf.sem_op  = -1;
		mybuf.sem_flg = 0;
		
		
		close(fd[0]);
      		size = write(fd[1], "Hello, child!", 14);
      		close(fd[1]);

      		close(FD[1]);
      		SIZE = read(FD[0], RESstring, 15);
      		close(FD[0]);



    
    	
		if(semop(semid, &mybuf, 1) < 0){
			printf("Can\'t wait for condition\n");
			exit(-1);
		}  
      
		printf("The condition is present\n");




      		printf("Parent exit, result: %s\n", RESstring);
	}
	if (result == 0) {/* Child process */
		close(fd[1]);
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
   	}	
   	return 0;
}
