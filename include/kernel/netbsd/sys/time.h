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



#ifndef LIBC_KERNEL_NETBSD_SYS_TIME_H
# define LIBC_KERNEL_NETBSD_SYS_TIME_H


/* types */
# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef int suseconds_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef int time_t;
# endif
# ifndef timeval
#  define timeval timeval
struct timeval
{
	long tv_sec;
	long tv_usec;
};
# endif


/* constants */
# define ITIMER_REAL	0
# define ITIMER_VIRTUAL	1
# define ITIMER_PROF	2

#endif /* !LIBC_KERNEL_NETBSD_SYS_TIME_H */
