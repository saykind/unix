#include <sys/types.h>
#include <stdio.h>

int main(void) {
	uid_t uid = getuid();
	gid_t gid = getgid();
	printf("uid=%d\ngid=%d\n", getuid(), getgid());
//	perror("Result");
	return 0;
}
