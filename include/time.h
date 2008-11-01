/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



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


/* constants */
# define CLOCKS_PER_SEC		1000000


/* functions */
clock_t clock(void);
struct tm * gmtime(time_t const * t);
struct tm * gmtime_r(time_t const * t, struct tm * ret);
struct tm * localtime(time_t const * t);
struct tm * localtime_r(time_t const * t, struct tm * ret);
time_t mktime(struct tm * timep);
int nanosleep(struct timespec * requested, struct timespec * remaining);
size_t strftime(char * s, size_t maxsize, char const * format,
		struct tm * timep);
time_t time(time_t * t);
void tzset(void);

#endif /* !LIBC_TIME_H */
