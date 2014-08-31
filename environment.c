#include <stdio.h>

int main(int argv, char *argc[], char *env[]) {
	while (*env) {
		printf("%s\n", *env);
		env++;
	}
	return 0;
}
