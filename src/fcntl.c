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



#include "errno.h"
#include "syscalls.h"
#include "fcntl.h"


/* functions */
/* creat */
#ifndef SYS_creat
# ifdef SYS_open
int creat(const char * filename, mode_t mode)
{
	return open(filename, O_CREAT | O_TRUNC | O_WRONLY, mode);
}
# else
#  warning Unsupported platform: creat() is missing
int creat(const char * filename, mode_t mode)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif


/* fcntl */
#ifndef SYS_fcntl
# warning Unsupported platform: fcntl() is missing
int fcntl(int fd, int cmd, ...)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* flock */
#ifndef SYS_flock
# warning Unsupported platform: flock() is missing
int flock(int fd, int operation)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* open */
#ifndef SYS_open
# warning Unsupported platform: open() is missing
int open(char const * filename, int flags, ...)
{
	errno = ENOSYS;
	return -1;
}
#endif
