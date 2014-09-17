#include <stdio.h>

int main(int argv, char *argc[], char *env[]) {
	while (*env) {
		printf("%s\n", *env);
		env++;
	}
	int i;
	printf("\targv = %d\n", argv);
	for (i = 0; i < argv; i++) {
		printf("[%d]\t%s\n", i, argc[i]);
	}

	return 0;
}
