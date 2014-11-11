#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define red     "\x1b[31m"
#define green   "\x1b[32m"
#define yellow  "\x1b[33m"
#define blue    "\x1b[34m"
#define magneta "\x1b[35m"
#define cyan    "\x1b[36m"
#define reset   "\x1b[0m"

int list(char *dirname);
int listall(char *dirname);
int print(char *name);

int main(int argv, char *argc[], char *env[]) {
	int i; char c;
//	for (i = 0; i < argv; i++)  printf("argc[%d] = '%s'\n", i, argc[i]);
	if (argv == 1) {
		return list(getenv("PWD"));
	}
	if (*(argc[1]) == '-') {
		c= *(argc[1]+1);
		switch(c) {
			case 'a': {listall(getenv("PWD")); break;}
			case 'q': {printf("quiet\n"); break;}
			default: {printf("Unknown flag '%s'\n", argc[1]); break;}
		}
	} else {
		return list(argc[1]);
	}
	return -1;
}


int listall(char *dirname) {
	char *name;
	DIR *dp = opendir(dirname); if(dp == NULL) {perror("opendir");}
	struct dirent *sd = readdir(dp); 
	while (sd) {
		print(sd->d_name);
		sd = readdir(dp);
	}
	printf("\n");
	return 0;
}
int list(char *dirname) {
	char *name;
	DIR *dp = opendir(dirname); if(dp == NULL) {perror("opendir");}
	struct dirent *sd = readdir(dp); 
	while (sd) {
		name = sd->d_name;
		if (*name != '.')
			print(name);
		sd = readdir(dp);
	}
	printf("\n");
	return 0;
}

int print(char *name) {
	struct stat st;
	if (stat(name, &st) != 0) {perror("stat"); return -1;}
	if (S_ISDIR(st.st_mode))
		return printf(blue "%s  " reset, name);
	if (st.st_mode & S_IXUSR) 
			return printf(green "%s  " reset, name);
	return printf("%s  ", name);	
}	
