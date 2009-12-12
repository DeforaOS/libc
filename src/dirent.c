/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



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
# ifdef SYS_getdentries
#  define getdents(fd, buf, size) getdirentries(fd, buf, size, NULL)
# endif

struct dirent * readdir(DIR * dir)
{
	static struct dirent de;
	ssize_t slen;
	size_t len;
	const size_t off = sizeof(de) - sizeof(de.d_name);

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
