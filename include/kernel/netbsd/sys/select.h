/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_NETBSD_SYS_SELECT_H
# define LIBC_KERNEL_NETBSD_SYS_SELECT_H


/* types */
# ifndef fd_set
#  define fd_set fd_set
typedef struct _fd_set
{
	int fds_bits[8];
} fd_set;
# endif

# ifndef timeval
#  define timeval timeval
struct timeval
{
	long tv_sec;
	long tv_usec;
};
# endif


/* macros */
# define FD_CLR(fd, fdset)	\
	((fdset)->fds_bits[(fd) / 32] &= ~(1 << ((fd) % 8)))
# define FD_ISSET(fd, fdset)	\
	((fdset)->fds_bits[(fd) / 32] & (1 << ((fd) % 8)))
# define FD_SET(fd, fdset)	\
	((fdset)->fds_bits[(fd) / 32] |= (1 << ((fd) % 8)))
# define FD_ZERO(fdset)		\
	memset(fdset, 0, sizeof(fd_set))


/* constants */
# define FD_SETSIZE	256

#endif /* !LIBC_KERNEL_NETBSD_SYS_SELECT_H */
