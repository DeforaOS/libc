/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



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

	if((fd = open(name, O_RDONLY)) < 0)
		return NULL;
	if(fcntl(fd, F_SETFD, FD_CLOEXEC) != 0
			|| fstat(fd, &st) != 0)
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
#if defined(SYS_getdents) || defined(SYS_getdirentries)
int getdents(int fd, char * buf, size_t nbuf);
int getdirentries(int fd, char * buf, size_t nbuf, char * basep);

struct dirent * readdir(DIR * dir)
{
	static struct dirent de;
	size_t len;
	const size_t off = sizeof(de) - sizeof(de.d_name);

	for(;;)
	{
		if(dir->len == 0)
		{
#ifdef SYS_getdents
			if((len = getdents(dir->fd, dir->buf, sizeof(dir->buf)))
#else /* SYS_getdirentries */
			if((len = getdirentries(dir->fd, dir->buf, sizeof(dir->buf), NULL))
#endif
					== (size_t)-1) /* XXX cast */
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
