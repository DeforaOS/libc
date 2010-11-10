/* $Id$ */
/* Copyright (c) 2010 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_LINUX_FCNTL_H
# define LIBC_KERNEL_LINUX_FCNTL_H


/* types */
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef signed int pid_t;
# endif

struct flock
{
	short l_type;
	short l_whence;
	off_t l_start;
	off_t l_len;
	pid_t l_pid;
};


/* constants */
# define F_DUPFD	0
# define F_GETFD	1
# define F_SETFD	2
# define F_GETFL	3
# define F_SETFL	4
# define F_GETLK	5	/* XXX 12 for 64 bits */
# define F_SETLK	6	/* XXX 13 for 64 bits */
# define F_SETLKW	7	/* XXX 14 for 64 bits */
# define F_SETOWN	8
# define F_GETOWN	9

# define FD_CLOEXEC	1

# define F_RDLCK	0
# define F_WRLCK	1
# define F_UNLCK	2

# define O_RDONLY	000000
# define O_WRONLY	000001
# define O_RDWR		000002

# define O_CREAT	000100
# define O_EXCL		000200
# define O_NOCTTY	000400
# define O_TRUNC	001000

# define O_APPEND	002000
# define O_NONBLOCK	004000
# define O_SYNC		010000
# define O_DSYNC	O_SYNC
# define O_RSYNC	O_SYNC

# define O_ACCMODE	(O_WRONLY | O_RDWR)

#endif /* !LIBC_KERNEL_LINUX_FCNTL_H */
