/* $Id$ */
/* Copyright (c) 2012-2017 Pierre Pronchery <khorben@defora.org> */
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



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


/* clock */
static int _clock(char const * progname)
{
	clock_t c;

	printf("%s: Testing clock()\n", progname);
	if((c = clock()) == (clock_t)-1)
	{
		perror("clock");
		return -1;
	}
	return 0;
}


/* getdate */
static int _getdate(char const * progname)
{
	char const date[] = "1970-01-01 00:00:00";

	printf("%s: Testing getdate()\n", progname);
	if(unsetenv("DATEMSK") != 0)
	{
		perror("unsetenv");
		return -1;
	}
	if(getdate(date) != NULL)
	{
		perror("getdate");
		return -1;
	}
	if(getdate_err != 1)
	{
		perror("getdate_err");
		return -1;
	}
	return 0;
}


/* mktime */
static int _mktime(char const * progname)
{
	time_t t;
	struct tm tm;

	printf("%s: Testing mktime()\n", progname);
	tzset();
	t = time(NULL);
	printf("time: %ld\n", t);
	if(localtime_r(&t, &tm) == NULL)
	{
		perror("localtime_r");
		return -1;
	}
	printf("localtime: %02d/%02d/%4d %02d:%02d:%02d\n",
			tm.tm_mday, tm.tm_mon, tm.tm_year + 1900,
			tm.tm_hour, tm.tm_min, tm.tm_sec);
	if((t = mktime(&tm)) == (time_t)-1 || t == 0)
	{
		perror("mktime");
		return -1;
	}
	printf("mktime: %ld\n", t);
	return 0;
}


/* strftime */
static int _strftime(char const * progname, char const * format,
		char const * expected)
{
	time_t t = 0;
	struct tm tm;
	char buf[128];

	printf("%s: Testing strftime()\n", progname);
	if(gmtime_r(&t, &tm) == NULL)
	{
		perror("gmtime");
		return -1;
	}
	if(strftime(buf, sizeof(buf), format, &tm) == 0)
	{
		perror("strftime");
		return -1;
	}
	if(strcmp(buf, expected) == 0)
		return 0;
	printf("%s: Obtained \"%s\" (expected: \"%s\")\n", progname, buf,
			expected);
	return -1;
}


/* strptime */
static int _strptime(char const * progname)
{
	char const buf[] = "1970/01/01 00:00:00";
	char const format[] = "%Y/%m/%d %H:%M:%S";
	struct tm tm;

	printf("%s: Testing strptime()\n", progname);
	if(strptime(buf, format, &tm) == NULL)
	{
		perror("strptime");
		return -1;
	}
	if(tm.tm_year != 0 || tm.tm_mon != 0 || tm.tm_mday != 1
			|| tm.tm_hour != 0 || tm.tm_min != 0 || tm.tm_sec != 0)
	{
		fputs("strptime: Invalid conversion\n", stderr);
		return -1;
	}
	return 0;
}


/* tzset */
static int _tzset(char const * progname)
{
	printf("%s: Testing tzset()\n", progname);
	tzset();
	printf("STD: %s, DST %s\n", tzname[0], tzname[1]);
	printf("daylight: %d, timezone %ld\n", daylight, timezone);
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int res = 0;
	(void) argc;

	res += _clock(argv[0]);
	res += _getdate(argv[0]);
	res += _mktime(argv[0]);
	res += _strftime(argv[0], "%H:%M:%S", "00:00:00");
	res += _strftime(argv[0], "%B", "January");
	res += _strftime(argv[0], "%b", "Jan");
	res += _strftime(argv[0], "%A", "Thursday");
	res += _strftime(argv[0], "%a", "Thu");
	res += _strftime(argv[0], "%e", " 1");
	res += _strptime(argv[0]);
	res += _tzset(argv[0]);
	return (res == 0) ? 0 : 2;
}
