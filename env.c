#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[]) {
	if (argv < 2) {return 0;}
	char *s = getenv(argc[1]);
	(s==0) ? printf("variable not defined\n") : printf("%s=%s\n",argc[1],s);
	return 0;
}
