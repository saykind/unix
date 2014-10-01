#include <stdio.h>

int main(int argv, char *argc[]) {
	int i;
//	printf("argv = %d\n", argv);
	for (i = 0; i < argv; i++) {
		printf("[%d]\t%s\n", i, argc[i]);
	}
	return 0;
}
