/* $Id$ */
/* Copyright (c) 2005-2012 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#include "sys/stat.h"
#include "fcntl.h"
#include "unistd.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "errno.h"
#include "syscalls.h"
#include "dirent.h"


/* types */
struct _DIR
{
	int fd;
	char buf[PAGESIZE];
	size_t len;
};


/* functions */
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


/* dirfd */
int dirfd(DIR * dir)
{
	if(dir == NULL)
	{
		errno = EINVAL;
		return -1;
	}
	return dir->fd;
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
	if((dir = malloc(sizeof(*dir))) == NULL)
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
# ifdef SYS_getdirentries
int getdirentries(int fd, char * buf, size_t nbuf, char * basep);
#  define getdents(fd, buf, size) getdirentries(fd, buf, size, NULL)
# endif

struct dirent * readdir(DIR * dir)
{
	static struct dirent de;
	ssize_t slen;
	size_t len;
	const size_t off = offsetof(struct dirent, d_name);

	for(;;)
	{
		if(dir->len == 0)
		{
			if((slen = getdents(dir->fd, dir->buf, sizeof(
								dir->buf))) < 0)
				return NULL;
			len = slen;
			dir->len = len;
		}
		memcpy(&de, dir->buf, off);
		len = de.d_reclen;
		if(len > sizeof(de) || len > dir->len || len <= off)
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
struct dirent * readdir(DIR * dir)
{
	errno = ENOSYS;
	return NULL;
}
#endif


/* rewinddir */
void rewinddir(DIR * dir)
{
	if(lseek(dir->fd, 0, SEEK_SET) != 0)
	{
		close(dir->fd);
		dir->fd = -1;
		dir->len = 0;
	}
	dir->len = 0;
}
