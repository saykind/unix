#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define MAXLINE 100

int main(int argv, char *argc[]) {
	if (argv != 2) {
		fprintf(stderr, "One argument needed.\n");
		return 0;
	}
	FILE *fp = fopen(argc[1],"r");
	int errval = errno;
	if (!fp) {
		fprintf(stderr, "Can't open '%s'.\nError No. %d", argc[1], errval);
		return 0;}

	int sec; char c; int i;
	char *cmd; cmd = (char *) malloc(MAXLINE);
	do {
		fscanf(fp,"%d", &sec);
		c = fgetc(fp);
		c = fgetc(fp);
		i = 0;
		while ((c != '\n') && (c != EOF)) {
			*(cmd + i++) = c;
			c = fgetc(fp);
		}	*(cmd + i) = '\n'; *(cmd + i) = '\0';
		//printf("<%s>\n",cmd);//TODO
		sleep(sec);
		system(cmd);
	}	while (c != EOF);

	free(cmd);
	return 0;
}
