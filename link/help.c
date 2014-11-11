#include <unistd.h>
int link(char *, char *)	// hard link
int symlink(char *, char *)	// soft link
int unlink(char *filename)	// rm file, hard link, soft link
int rmdir(char *dirname)	// rm directory

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
int	stat(char *filename, struct stat *buf)		// Goes after link
int	lstat(char *filename, struct stat *buf)		// Doesn't by link
int	fstat(int fd, struct stat *buf)
struct stat {
	dev_t         st_dev;      /* устройство */
	ino_t         st_ino;      /* inode */
	mode_t        st_mode;     /* режим доступа */
	nlink_t       st_nlink;    /* количество жестких ссылок */
	uid_t         st_uid;      /* ID пользователя-владельца */
	gid_t         st_gid;      /* ID группы-владельца */
	dev_t         st_rdev;     /* тип устройства (если это устройство) */
	off_t         st_size;     /* общий размер в байтах */
	unsigned long st_blksize;  /* размер блока ввода-вывода в файловой системе */
	unsigned long st_blocks;   /* количество выделенных блоков */
	time_t        st_atime;    /* время последнего доступа */
	time_t        st_mtime;    /* время последней модификации */
	time_t        st_ctime;    /* время последнего изменения */
};

#include <unistd.h>
readlink(char *linkname, char *buf, int buf_size);	// puts relative path from link to char *buf

#include <dirent.h>
DIR 		*opendir(const char *dirname)
struct dirent 	*readdir(DIR *dir)
struct dirent {
	no_t           d_ino;       /* inode number */
	off_t          d_off;       /* offset to the next dirent */
	unsigned short d_reclen;    /* length of this record */
	unsigned char  d_type;      /* type of file; not supported by all file system types */
	char           d_name[256]; /* filename */
};

#include <unistd.h>
int fseek(int fd, int offset, int place)          place = {SEEK_SET, SEEK_CUR, SEEK_END}

#include <unistd.h>
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
	      





