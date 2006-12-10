/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_TIME_H
# define LIBC_TIME_H


/* types */
# ifndef clock_t
#  define clock_t clock_t
typedef int clock_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef unsigned int size_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef int time_t;
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
time_t time(time_t * t);

#endif /* !LIBC_TIME_H */
