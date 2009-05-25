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
#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "syscalls.h"
#include "time.h"

#define min(a, b) ((a) < (b) ? (a) : (b))


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
	time_t u;

	if(t == NULL || ret == NULL)
	{
		errno = EINVAL;
		return NULL;
	}
	ret->tm_sec = *t % 60;
	u = (*t - ret->tm_sec) / 60;
	ret->tm_min = u % 60;
	u = (u - ret->tm_min) / 60;
	ret->tm_hour = u % 24;
	u = (u - ret->tm_hour) / 24;
	/* FIXME implement this correctly */
	ret->tm_wday = (u + 4) % 7;
	u = (u - ret->tm_wday) / 7;
	ret->tm_year = 70 + (u / 365);
	/* FIXME implement the rest */
	ret->tm_mday = 0;
	ret->tm_mon = 0;
	ret->tm_yday = 0;
	ret->tm_isdst = 0;
	/* FIXME implement this?
	ret->tm_gmtoff = 0; */
	return ret;
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
	if(gmtime_r(t, ret) == NULL)
		return NULL;
	/* FIXME apply timezone offset */
	return ret;
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
static char * _strftime_print(char * s, size_t * maxsize, char const * str,
		size_t size);
static char * _strftime_print_int(char * s, size_t * maxsize, int i);

size_t strftime(char * s, size_t maxsize, char const * format, struct tm * t)
{
	char * q = s;
	size_t pos;

	for(pos = 0; format[pos] != '\0'; pos++)
	{
		if(format[pos] != '%')
		{
			q = _strftime_print(q, &maxsize, &format[pos], 1);
			continue;
		}
		switch(format[++pos])
		{
			case '%':
				q = _strftime_print(q, &maxsize, &format[pos],
						1);
				break;
			case 'n':
				q = _strftime_print(q, &maxsize, "\n", 1);
				break;
			case 'p':
				q = _strftime_print(q, &maxsize, (t->tm_hour
							< 12) ? "a.m." : "p.m.",
						4);
				break;
			case 't':
				q = _strftime_print(q, &maxsize, "\t", 1);
				break;
			/* FIXME implement correctly */
			case 'b':
				break;
			case 'C':
				q = _strftime_print_int(q, &maxsize,
						t->tm_year / 100);
				break;
			case 'D':
				q = _strftime_print_int(q, &maxsize, t->tm_mon);
				q = _strftime_print(q, &maxsize, "/", 1);
				q = _strftime_print_int(q, &maxsize,
						t->tm_mday);
				q = _strftime_print(q, &maxsize, "/", 1);
				q = _strftime_print_int(q, &maxsize,
						t->tm_year);
				break;
			case 'd':
				q = _strftime_print_int(q, &maxsize,
						t->tm_mday);
				break;
			case 'e':
				break;
			case 'H':
				q = _strftime_print_int(q, &maxsize,
						t->tm_hour);
				break;
			case 'I':
				q = _strftime_print_int(q, &maxsize,
						t->tm_hour % 12);
				break;
			case 'j':
				q = _strftime_print_int(q, &maxsize,
						t->tm_yday);
				break;
			case 'M':
				q = _strftime_print_int(q, &maxsize, t->tm_min);
				break;
			case 'S':
				q = _strftime_print_int(q, &maxsize, t->tm_sec);
				break;
			case 'm':
				q = _strftime_print_int(q, &maxsize, t->tm_mon);
				break;
			case 'u':
				q = _strftime_print_int(q, &maxsize,
						t->tm_wday);
				break;
			case 'w':
				q = _strftime_print_int(q, &maxsize,
						t->tm_wday);
				break;
			case 'Y':
				q = _strftime_print_int(q, &maxsize,
						t->tm_year + 1900);
				break;
			case 'y':
				q = _strftime_print_int(q, &maxsize,
						t->tm_year);
				break;
			case 'Z':
				break;
			/* FIXME implement the rest */
			default:
				errno = EINVAL;
				return 0;
		}
	}
	if(q == NULL || maxsize == 0)
		return 0;
	*q = '\0';
	return strlen(s);
}

static char * _strftime_print(char * s, size_t * maxsize, char const * str,
		size_t size)
{
	if(s == NULL)
		return NULL;
	if(size == 0)
		size = strlen(str);
	size = min(*maxsize, size);
	strncpy(s, str, size);
	*maxsize -= size;
	return s + size;
}

static char * _strftime_print_int(char * s, size_t * maxsize, int i)
{
	char buf[16];
	int len;

	if((len = snprintf(buf, sizeof(buf), "%d", i)) <= 0)
		return s;
	return _strftime_print(s, maxsize, buf, len);
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
