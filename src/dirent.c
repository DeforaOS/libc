/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "sys/stat.h"
#include "errno.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdlib.h"
#include "limits.h"
#include "syscalls.h"
#include "dirent.h"


/* types */
struct _DIR
{
	int fd;
	char padding[PAGESIZE - sizeof(int)];
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
		close(fd);
	else
		dir->fd = fd;
	return dir;
}


/* readdir */
#ifdef SYS_getdents
int getdents(int fd, char * buf, size_t nbuf);
struct dirent * readdir(DIR * dir)
	/* FIXME only one directory can be read and analyzed at a time */
{
	static struct dirent de;

	if(getdents(dir->fd, (char*)&de, sizeof(de)) == -1)
		return NULL;
	return &de;
}
#endif
