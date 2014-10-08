#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#define N 6

int main()
{
	int     *array, *ready, *turn_, turn, j;
	int     shmid;
	int     new = 1;
	char    pathname[] = "06-3a.c";
	key_t   key;
	long    i;

	if((key = ftok(pathname,0)) < 0){
		printf("Can\'t generate key\n");
		exit(-1);
	}

	if((shmid = shmget(key, N*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){

	if(errno != EEXIST){
		printf("Can\'t create shared memory\n");
        	exit(-1);
	} else {
        	if((shmid = shmget(key, N*sizeof(int), 0)) < 0){
        		printf("Can\'t find shared memory\n");
        		exit(-1);
	 	}
		new = 0;
	}
	}

	if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
		printf("Can't attach shared memory\n");
		exit(-1);
	}
	ready = array + 3;
	turn_ = array + 5;
	ready[0] = 0; ready[1] = 0;
	j = 0;

	//prolog
		ready[j] = 1;
		*turn_ = 1-j;
		while(ready[1-j] && (*turn_ == (1-j))) ;

	if(new){
      		array[0] =  1;
      		array[1] =  0;
      		array[2] =  1;
   	} else {
		 array[0] += 1;
      		 for(i=0; i<2000000000L; i++);
      		 array[2] += 1;
   	}

   	printf
      	("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
      	array[0], array[1], array[2]);

	// epilog
		ready[j] = 0;


   if(shmdt(array) < 0){
      printf("Can't detach shared memory\n");
      exit(-1);
   }

   return 0;
}
