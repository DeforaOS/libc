/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "sys/stat.h"
#include "fcntl.h"
#include "unistd.h"
#include "errno.h"
#include "stdlib.h"
#include "dirent.h"
#include "syscalls.h"


/* types */
struct _DIR
{
	int fd;
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
	int fd;
	struct stat st;
	DIR * dir;

	if((fd = open(name, O_RDONLY)) != 0)
		return NULL;
	if(fstat(fd, &st) != 0)
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
#ifdef SYS_readdir
syscall1(struct dirent *, readdir, DIR *, dir);
#endif
