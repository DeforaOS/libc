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



#include "string.h"
#include "errno.h"
#include "../syscalls.h"
#include "sys/statvfs.h"


/* fstatvfs */
int fstatvfs(int fd, struct statvfs * buf)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* statvfs */
#if !defined(SYS_statvfs)
# if defined(SYS__statfs)
typedef long fsid_t;
struct statfs
{
	long f_type;
	long f_bsize;
	long f_blocks;
	long f_bfree;
	long f_bavail;
	long f_files;
	long f_ffree;
	fsid_t f_fsid;
	long f_namelen;
};
extern int _statfs(char const * path, struct statfs * buf);
int statvfs(char const * path, struct statvfs * buf)
{
	struct statfs fs;

	if(_statfs(path, &fs) != 0)
		return -1;
	memset(buf, 0, sizeof(*buf));
	buf->f_bsize = fs.f_bsize;
	buf->f_blocks = fs.f_blocks;
	buf->f_bfree = fs.f_bfree;
	buf->f_bavail = fs.f_bavail;
	buf->f_files = fs.f_files;
	buf->f_ffree = fs.f_ffree;
	buf->f_fsid = fs.f_fsid;
	buf->f_namemax = fs.f_namelen;
	return 0;
}
# else /* !SYS_statvfs && !SYS__statfs */
#  warning Unsupported platform: statvfs() is missing
int statvfs(char const * path, struct statvfs * buf)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif
