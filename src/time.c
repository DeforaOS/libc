/* $Id$ */
/* Copyright (c) 2005-2014 Pierre Pronchery <khorben@defora.org> */
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



#include "sys/resource.h"
#include "sys/time.h"
#include "ctype.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "errno.h"
#include "syscalls.h"
#include "time.h"

#define min(a, b) ((a) < (b) ? (a) : (b))


/* private */
/* variables */
static char const * _months[] =
{
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dec"
};

static char const * _months_long[] =
{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
};

static char const * _days[] =
{
	"Sun",
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat"
};

static char const * _days_long[] =
{
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};


/* public */
/* variables */
int daylight = 0;
long timezone = 0;

char * tzname[2] = { "UTC", "UTC" };
int getdate_err = 0;


/* functions */
/* clock */
clock_t clock(void)
{
#ifdef SYS_getrusage
	struct rusage ru;

	if(getrusage(RUSAGE_SELF, &ru) != 0)
		return (clock_t)-1;
	return ((ru.ru_utime.tv_sec + ru.ru_stime.tv_sec) * CLOCKS_PER_SEC)
		+ ((ru.ru_utime.tv_usec + ru.ru_stime.tv_usec)
				* (CLOCKS_PER_SEC / 1000000));
#else
	errno = ENOSYS;
	return (clock_t)-1;
#endif
}


/* clock_getres */
#ifndef SYS_clock_getres
int clock_getres(clockid_t clock_id, struct timespec * tp)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* clock_gettime */
#ifndef SYS_clock_gettime
int clock_gettime(clockid_t clock_id, struct timespec * tp)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* clock_settime */
#ifndef SYS_clock_settime
int clock_settime(clockid_t clock_id, struct timespec * tp)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* difftime */
double difftime(time_t time1, time_t time0)
{
	return (double)time1 - (double)time0;
}


/* getdate */
struct tm * getdate(char const * string)
{
	struct tm * ret = NULL;
	static struct tm tm;
	char const * datemsk;
	FILE * fp;
	char buf[80];
	size_t len;
	char * p;

	if((datemsk = getenv("DATEMSK")) == NULL)
	{
		getdate_err = 1;
		return NULL;
	}
	if((fp = fopen(datemsk, "r")) == NULL)
	{
		getdate_err = 2;
		return NULL;
	}
	while(fgets(buf, sizeof(buf), fp) != NULL)
	{
		if((len = strlen(buf)) > 0)
			buf[len - 1] = '\0';
		memset(&ret, 0, sizeof(ret));
		if((p = strptime(string, buf, &tm)) != NULL && *p == '\0')
		{
			ret = &tm;
			break;
		}
	}
	if(ret == NULL)
	{
		if(ferror(fp))
			getdate_err = 5;
		else
			getdate_err = 7;
	}
	fclose(fp);
	return ret;
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
	time_t ret;
	const time_t min = 60;
	const time_t hour = min * 60;
	const time_t day = hour * 24;
	const time_t month28 = day * 28;
	const time_t month30 = day * 30;
	const time_t month31 = day * 31;
	time_t month;
	const time_t year = day * 365;

	ret = timep->tm_sec;
	/* FIXME not accurate */
	ret += timep->tm_min * min;
	ret += timep->tm_hour * hour;
	ret += timep->tm_mday * day;
	month = (timep->tm_mon == 1 || timep->tm_mon == 3 || timep->tm_mon == 5
			|| timep->tm_mon == 7 || timep->tm_mon == 8
			|| timep->tm_mon == 10 || timep->tm_mon == 12)
		? month31 : ((timep->tm_mon != 2) ? month30 : month28);
	ret += timep->tm_mon * month;
	ret += (timep->tm_year - 70) * year;
	return ret;
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
static char * _strftime_print_int02(char * s, size_t * maxsize, int i);

size_t strftime(char * s, size_t maxsize, char const * format, struct tm * t)
{
	char * q = s;
	size_t pos;
	char const * p;

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
			case 'A':
				if(t->tm_wday >= (int)(sizeof(_days_long)
							/ sizeof(*_days_long)))
					break;
				p = _days_long[t->tm_wday];
				q = _strftime_print(q, &maxsize, p, strlen(p));
				break;
			case 'a':
				if(t->tm_wday >= (int)(sizeof(_days)
							/ sizeof(*_days)))
					break;
				p = _days[t->tm_wday];
				q = _strftime_print(q, &maxsize, p, strlen(p));
				break;
			case 'B':
				if(t->tm_mon >= (int)(sizeof(_months_long)
							/ sizeof(*_months_long)))
					break;
				p = _months_long[t->tm_mon];
				q = _strftime_print(q, &maxsize, p, strlen(p));
				break;
			case 'b':
			case 'h':
				if(t->tm_mon >= (int)(sizeof(_months)
							/ sizeof(*_months)))
					break;
				p = _months[t->tm_mon];
				q = _strftime_print(q, &maxsize, p, strlen(p));
				break;
			case 'C':
				q = _strftime_print_int(q, &maxsize,
						t->tm_year / 100);
				break;
			case 'D':
			case 'x':
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
			case 'e': /* TODO: Test */
				q = _strftime_print_int(q, &maxsize, t->tm_mday);
				if(q[0] == '0')
					q[0] = ' ';
				break;
			case 'F':
				q = _strftime_print_int(q, &maxsize, t->tm_year);
				q = _strftime_print(q, &maxsize, "-", 1);
				q = _strftime_print_int(q, &maxsize, t->tm_mon);
				q = _strftime_print(q, &maxsize, "-", 1);
				q = _strftime_print_int(q, &maxsize, t->tm_mday);
				break;
			case 'H':
				q = _strftime_print_int02(q, &maxsize,
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
			case 'k':
				q = _strftime_print_int(q, &maxsize, t->tm_hour);
				if(q[0] == '0')
					q[0] = ' ';
				break;
			case 'l':
				q = _strftime_print_int(q, &maxsize, t->tm_hour % 12);
				if(q[0] == '0')
					q[0] = ' ';
				break;
			case 'M':
				q = _strftime_print_int02(q, &maxsize,
						t->tm_min);
				break;
			case 'm':
				q = _strftime_print_int(q, &maxsize, t->tm_mon);
				break;
			case 'n':
				q = _strftime_print(q, &maxsize, "\n", 1);
				break;
			case 'P':
				q = _strftime_print(q, &maxsize, (t->tm_hour
							< 12) ? "am" : "pm", 4);
				break;
			case 'p':
				q = _strftime_print(q, &maxsize, (t->tm_hour
							< 12) ? "AM" : "PM",
						4);
				break;
			case 'R':
				q = _strftime_print_int(q, &maxsize, t->tm_hour);
				q = _strftime_print(q, &maxsize, ":", 1);
				q = _strftime_print_int(q, &maxsize, t->tm_min);
				break;
			case 'r':
				q = _strftime_print_int(q, &maxsize,
						t->tm_hour % 12);
				q = _strftime_print(q, &maxsize, ":", 1);
				q = _strftime_print_int(q, &maxsize, t->tm_min);
				q = _strftime_print(q, &maxsize, ":", 1);
				q = _strftime_print_int(q, &maxsize, t->tm_sec);
				q = _strftime_print(q, &maxsize, " ", 1);
				q = _strftime_print(q, &maxsize, (t->tm_hour < 12)
						? "AM" : "PM", 4);
				break;
			case 'S':
				q = _strftime_print_int02(q, &maxsize,
						t->tm_sec);
				break;
			case 's':
				q = _strftime_print_int(q, &maxsize, time(NULL));
				break;
			case 'T':
				q = _strftime_print_int(q, &maxsize, t->tm_hour);
				q = _strftime_print(q, &maxsize, ":", 1);
				q = _strftime_print_int(q, &maxsize, t->tm_min);
				q = _strftime_print(q, &maxsize, ":", 1);
				q = _strftime_print_int(q, &maxsize, t->tm_sec);
				break;
			case 't':
				q = _strftime_print(q, &maxsize, "\t", 1);
				break;
			case 'X':
				q = _strftime_print_int(q, &maxsize,
						t->tm_hour);
				q = _strftime_print(q, &maxsize, ":", 1);
				q = _strftime_print_int(q, &maxsize,
						t->tm_min);
				q = _strftime_print(q, &maxsize, ":", 1);
				q = _strftime_print_int(q, &maxsize, t->tm_sec);
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

static char * _strftime_print_int02(char * s, size_t * maxsize, int i)
{
	char buf[16];
	int len;

	if((len = snprintf(buf, sizeof(buf), "%02d", i)) <= 0)
		return s;
	return _strftime_print(s, maxsize, buf, len);
}


/* strptime */
char * strptime(char const * buf, char const * format, struct tm * tm)
{
	int e = errno;
	char * p;
	char const * q;

	memset(tm, 0, sizeof(*tm));
	for(p = (char *)buf, q = format; *p != '\0' && *q != '\0'; q++)
	{
		if(isspace(*q))
		{
			for(; isspace(*p); p++);
			continue;
		}
		if(*q != '%')
		{
			if(*p != *q)
				break;
			p++;
			continue;
		}
		switch(*(++q))
		{
			case 'd':
				/* day of the month */
				errno = 0;
				tm->tm_mday = strtol(p, &p, 10);
				if(errno != 0 || tm->tm_mday < 1
						|| tm->tm_mday > 31)
					return NULL;
				break;
			case 'H':
				/* hour (24-hour clock) */
				errno = 0;
				tm->tm_hour = strtol(p, &p, 10);
				if(errno != 0 || tm->tm_hour < 0
						|| tm->tm_hour > 23)
					return NULL;
				break;
			case 'M':
				/* minute */
				errno = 0;
				tm->tm_min = strtol(p, &p, 10);
				if(errno != 0 || tm->tm_min < 0
						|| tm->tm_min > 60)
					return NULL;
				break;
			case 'm':
				/* month number */
				errno = 0;
				tm->tm_mon = strtol(p, &p, 10);
				if(errno != 0 || tm->tm_mon < 1
						|| tm->tm_mon > 12)
					return NULL;
				tm->tm_mon--;
				break;
			case 'S':
				/* seconds */
				errno = 0;
				tm->tm_sec = strtol(p, &p, 10);
				if(errno != 0 || tm->tm_sec < 0
						|| tm->tm_sec > 61)
					return NULL;
				break;
			case 'Y':
				/* year, including the century */
				errno = 0;
				tm->tm_year = strtol(p, &p, 10);
				if(errno != 0)
					return NULL;
				tm->tm_year -= 1970;
				break;
			default:
				/* FIXME implement more */
				errno = ENOSYS;
				return NULL;
		}
	}
	if(*q != '\0')
		return NULL;
	errno = e;
	return p;
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
	/* FIXME implement, set daylight, timezone and tzname */
}
