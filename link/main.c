#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#define red     "\x1b[31m"
#define green   "\x1b[32m"
#define yellow  "\x1b[33m"
#define blue    "\x1b[34m"
#define magneta "\x1b[35m"
#define cyan    "\x1b[36m"
#define reset   "\x1b[0m"

int list(char *dirname);

int main(int argv, char *argc[], char *env[]) {
	int i; char c;
	if (argv == 1) 
		return list(getenv("PWD"));
	if (*(argc[1]) == '-') {
		switch(*(argc[1]+1)) {
			case 'a': {list(getenv("PWD")); break;}
			default: {printf("Unknown flag '%s'\n", argc[1]); break;}
		}
	} else {
		return list(argc[1]);
	}
	return -1;
}

int list(char *dirname) {
	char *name;
	DIR *dp = opendir(dirname); if(dp == NULL) {perror("opendir");}
	struct dirent *sd = readdir(dp);
       	printf("type\townuid\towngid\tmodification time\tsize\tname\n");
	printf("------------------------------------\n");	
	while (sd) {
		if (*sd->d_name == '.') {
			sd = readdir(dp);
			continue;
		}
		char *to = (char *) malloc(100);
		char *name = (char *) malloc(100);
		sprintf(name, "%s/%s", dirname, sd->d_name);
		struct stat st;
		if (lstat(name, &st) != 0) {perror("lstat"); return -1;}
		if (S_ISDIR(st.st_mode))
			printf("direct");
		if (S_ISREG(st.st_mode))
			printf("regular");
		if (S_ISLNK(st.st_mode)) {
			if (readlink(name, to, 100) < 0) 
				perror("readlink");
			strcat(to, "\0");
			printf("symlink");		
		} else 
			to = NULL;
		if (S_ISCHR(st.st_mode))
			printf("chr dev");		
		if (S_ISBLK(st.st_mode))
			printf("blk dev");		
		if (S_ISFIFO(st.st_mode))
			printf("fifo");		
		printf("\t%u", st.st_uid);
		printf("\t%u", st.st_gid);
		struct tm *timeptr = localtime(&st.st_mtime);
		printf("\t%.2d.%.2d %d:%d:%d\t", 
				timeptr->tm_mday, 
				timeptr->tm_mon,
				timeptr->tm_hour,
				timeptr->tm_min,
				timeptr->tm_sec);
		printf("\t%ld\t", st.st_size);	
		if (st.st_mode & S_IXUSR) {
			if (S_ISDIR(st.st_mode)) 
				printf(blue "%s  " reset, sd->d_name);
			else
				if (S_ISLNK(st.st_mode))
					printf(cyan "%s  " reset, sd->d_name);
				else
					printf(green "%s  " reset, sd->d_name);
		} else 
			printf("%s  ", sd->d_name);
		if (to)
			printf("->%s", to);
		printf("\n");
		free(name);
		free(to);
		sd = readdir(dp);
	}
	printf("\n");
	return 0;
}
