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



#include "sys/resource.h"
#include "sys/time.h"
#include "stdlib.h"
#include "errno.h"
#include "syscalls.h"
#include "time.h"


/* clock */
clock_t clock(void)
{
#ifdef SYS_getrusage
	struct rusage ru;

	if(getrusage(RUSAGE_SELF, &ru) != 0)
		return -1;
	return ((ru.ru_utime.tv_sec + ru.ru_stime.tv_sec) * CLOCKS_PER_SEC)
		+ ((ru.ru_utime.tv_usec + ru.ru_stime.tv_usec)
				* (CLOCKS_PER_SEC / 1000000));
#else
	errno = ENOSYS;
	return -1;
#endif
}


/* gmtime */
struct tm * gmtime(time_t const * t)
{
	static struct tm ret;

	return gmtime_r(t, &ret);
}


/* gmtime_r */
struct tm * gmtime_r(time_t const * t, struct tm * ret)
{
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* localtime */
struct tm * localtime(time_t const * t)
{
	static struct tm ret;

	tzset();
	if(localtime_r(t, &ret) == NULL)
		return NULL;
	return &ret;
}


/* localtime_r */
struct tm * localtime_r(time_t const * t, struct tm * ret)
{
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* mktime */
time_t mktime(struct tm * timep)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* nanosleep */
#ifndef SYS_nanosleep
# warning Unsupported platform: nanosleep() is missing
int nanosleep(struct timespec * requested, struct timespec * remaining)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* strftime */
size_t strftime(char * s, size_t maxsize, char const * format,
		struct tm * timep)
{
	/* FIXME implement */
	if(maxsize > 0)
		*s = '\0';
	errno = ENOSYS;
	return 0;
}


/* time */
time_t time(time_t * t)
{
	struct timeval tv;

	if(gettimeofday(&tv, NULL) != 0)
		return -1;
	if(t != NULL)
		*t = tv.tv_sec;
	return tv.tv_sec;
}


/* tzset */
void tzset(void)
{
	/* FIXME implement */
}
