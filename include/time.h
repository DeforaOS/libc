/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_TIME_H
# define LIBC_TIME_H

# include "compat/time.h"


/* types */
# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
# endif
/* FIXME also define clockid_t timer_t */

struct tm
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

struct timespec
{
	time_t tv_sec;
	long tv_nsec;
};

struct itimespec
{
	struct timespec it_interval;
	struct timespec it_value;
};


/* functions */
struct tm * localtime(time_t const * t);
int nanosleep(struct timespec * requested, struct timespec * remaining);
time_t time(time_t * t);

#endif /* !LIBC_TIME_H */
