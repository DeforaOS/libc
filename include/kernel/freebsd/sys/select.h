/* $Id$ */
/* Copyright (c) 2008-2012 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_FREEBSD_SYS_SELECT_H
# define LIBC_KERNEL_FREEBSD_SYS_SELECT_H


/* constants */
# define FD_SETSIZE	1024


/* types */
# ifndef fd_set
#  define fd_set fd_set
typedef struct _fd_set
{
	unsigned long fds_bits[((FD_SETSIZE) + (((sizeof(unsigned long) * 8))
				- 1)) / ((sizeof(unsigned long) * 8))];
} fd_set;
# endif

# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef long suseconds_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef int time_t;
# endif
# ifndef timeval
#  define timeval timeval
struct timeval
{
#ifdef __arm__
	time_t tv_sec;
#else
	long tv_sec;
#endif
	suseconds_t tv_usec;
};
# endif


/* macros */
# define FD_ZERO(fdset)							\
	do								\
	{								\
		fd_set * p = fdset;					\
		size_t n;						\
									\
		while(n < (sizeof(fdset->fds_bits)			\
					/ sizeof(fdset->fds_bits[0])))	\
			fdset->fds_bits[n++] = 0;			\
	}								\
	while(0)

#endif /* !LIBC_KERNEL_FREEBSD_SYS_SELECT_H */
