/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "sys/stat.h"
#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "syscalls.h"
#include "dirent.h"


/* types */
struct _DIR
{
	int fd;
	char buf[PAGESIZE];
	size_t len;
};


/* closedir */
int closedir(DIR * dir)
{
	if(dir == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	if(close(dir->fd) != 0)
		return -1;
	free(dir);
	return 0;
}


/* opendir */
DIR * opendir(char const * name)
{
	DIR * dir;
	int fd;
	struct stat st;

	if((fd = open(name, O_RDONLY)) == -1)
		return NULL;
	if(fcntl(fd, F_SETFD, FD_CLOEXEC) != 0 || fstat(fd, &st) != 0)
	{
		close(fd);
		return NULL;
	}
	if(!S_ISDIR(st.st_mode))
	{
		close(fd);
		errno = ENOTDIR;
		return NULL;
	}
	if((dir = malloc(sizeof(DIR))) == NULL)
	{
		close(fd);
		return NULL;
	}
	dir->fd = fd;
	dir->len = 0;
	return dir;
}


/* readdir */
#if defined(SYS_getdents)
int getdents(int fd, char * buf, size_t nbuf);
struct dirent * readdir(DIR * dir)
{
	static struct dirent de;
	size_t len;
	const size_t off = sizeof(de) - sizeof(de.d_name);

	for(;;)
	{
		if(dir->len == 0)
		{
			if((len = getdents(dir->fd, dir->buf, sizeof(dir->buf)))
					== (size_t)-1)
				return NULL;
			dir->len = len;
		}
		memcpy(&de, dir->buf, off);
		len = de.d_reclen;
		if(len > sizeof(de) || len > dir->len)
		{
			dir->len = 0;
			return NULL;
		}
		memcpy(de.d_name, &dir->buf[off], len - off);
		dir->len -= len;
		memmove(dir->buf, &dir->buf[len], dir->len);
		if(de.d_ino != 0)
			break;
	}
	return &de;
}
#elif !defined(SYS_readdir)
# warning Unsupported platform: readdir() is missing
#endif
