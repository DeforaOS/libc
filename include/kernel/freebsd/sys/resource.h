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



#ifndef LIBC_KERNEL_FREEBSD_SYS_RESOURCE_H
# define LIBC_KERNEL_FREEBSD_SYS_RESOURCE_H


/* types */
# ifndef rlim_t
#  define rlim_t rlim_t
typedef long long rlim_t;
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
# define timeval timeval
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

# ifndef rlimit
#  define rlimit rlimit
struct rlimit
{
	rlim_t rlim_cur;
	rlim_t rlim_max;
};
# endif

# ifndef rusage
#  define rusage rusage
struct rusage
{
	struct timeval ru_utime;
	struct timeval ru_stime;
	long ru_maxrss;
	long ru_ixrss;
	long ru_idrss;
	long ru_isrss;
	long ru_minflt;
	long ru_majflt;
	long ru_nswap;
	long ru_inblock;
	long ru_oublock;
	long ru_msgsnd;
	long ru_msgrcv;
	long ru_nsignals;
	long ru_nvcsw;
	long ru_nivcsw;
};
# endif


/* constants */
# define PRIO_PROCESS	0
# define PRIO_PGRP	1
# define PRIO_USER	2

# define RUSAGE_SELF		0
# define RUSAGE_CHILDREN	-1

#endif /* !LIBC_KERNEL_FREEBSD_SYS_RESOURCE_H */
