/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_NETBSD_SYS_RESOURCE_H
# define LIBC_KERNEL_NETBSD_SYS_RESOURCE_H


/* types */
# ifndef rlim_t
#  define rlim_t rlim_t
typedef long long rlim_t;
# endif

# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef int suseconds_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef unsigned int time_t;
# endif
# ifndef timeval
# define timeval timeval
struct timeval
{
	time_t tv_sec;
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

#endif /* !LIBC_KERNEL_NETBSD_SYS_RESOURCE_H */
