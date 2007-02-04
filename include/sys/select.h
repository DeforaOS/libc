/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SYS_SELECT_H
# define LIBC_SYS_SELECT_H


/* types */
# ifndef fd_set
#  define fd_set fd_set
typedef struct _fd_set fd_set;
# endif
# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef int suseconds_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef long long time_t;
# endif
# ifndef timeval
#  define timeval timeval
struct timeval
{
	time_t tv_sec;
	suseconds_t tv_usec;
};
# endif

struct itimerval
{
	struct timeval it_interval;
	struct timeval it_value;
};


/* functions */
int select(int fdcnt, fd_set * rfds, fd_set * wfds, fd_set * efds,
		struct timeval * timeout);

#endif /* !LIBC_SYS_SELECT_H */
