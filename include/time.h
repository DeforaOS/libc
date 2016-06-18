/* $Id$ */
/* Copyright (c) 2005-2016 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#ifndef LIBC_TIME_H
# define LIBC_TIME_H

# include "compat.h"
# include "compat/time.h"


/* types */
# ifndef size_t
#  define size_t __size_t
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

# ifndef timespec
#  define timespec timespec
struct timespec
{
	time_t tv_sec;
	long tv_nsec;
};
# endif

struct itimespec
{
	struct timespec it_interval;
	struct timespec it_value;
};


/* constants */
# define CLOCKS_PER_SEC		1000000


/* variables */
extern int daylight;
extern long timezone;

extern char * tzname[2];

extern int getdate_err;


/* functions */
clock_t clock(void);
int clock_getres(clockid_t clock_id, struct timespec * tp);
int clock_gettime(clockid_t clock_id, struct timespec * tp);
int clock_settime(clockid_t clock_id, struct timespec * tp);
double difftime(time_t time1, time_t time0);
struct tm * getdate(char const * string);
struct tm * gmtime(time_t const * t);
struct tm * gmtime_r(time_t const * t, struct tm * ret);
struct tm * localtime(time_t const * t);
struct tm * localtime_r(time_t const * t, struct tm * ret);
time_t mktime(struct tm * timep);
int nanosleep(struct timespec * requested, struct timespec * remaining);
size_t strftime(char * s, size_t maxsize, char const * format,
		struct tm * timep);
char * strptime(char const * buf, char const * format, struct tm * tm);
time_t time(time_t * t);
void tzset(void);

#endif /* !LIBC_TIME_H */
