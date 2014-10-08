#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10

int a = 0;
pthread_t thid[N];

void *mythread(void *dummy) {
	int num = *((int *) dummy);
	pthread_t mythid;
	mythid = pthread_self();
	if (num) pthread_join(thid[num-1], (void **)NULL);
	printf("\tThread #%d\t(id = %u)\tresult = %d\n", num, mythid, a);
	a++;
	//pthread_exit(NULL);
	return NULL;
}

int main(void){
	pthread_t mythid; 
	static int       i, result;

	for (i = 0; i < N; i++) {
		result = pthread_create(thid+i, (pthread_attr_t *)NULL, mythread, (void *)(&i));
		if(result != 0){
			printf ("Error on thread create, return value = %d\n", result);
			exit(-1);
		}
		printf("Thread #%d created, id = %u\n", i, thid[i]);
	}

	mythid = pthread_self();
	
	pthread_join(thid[N-1], (void **)NULL);
	printf("\tThread ##\t(id = %u)\tresult = %d\n", mythid, a);
	a++;
	
	return 0;
}
