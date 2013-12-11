/* $Id$ */
/* Copyright (c) 2012-2013 Pierre Pronchery <khorben@defora.org> */
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



#include <stdlib.h>
#include <stdio.h>
#include <time.h>


/* clock */
static int _clock(char const * progname)
{
	clock_t c;

	printf("%s: Testing clock()\n", progname);
	if((c = clock()) == (clock_t)-1)
		return -1;
	return 0;
}


/* getdate */
static int _getdate(char const * progname)
{
	char const date[] = "1970-01-01 00:00:00";

	printf("%s: Testing getdate()\n", progname);
	if(unsetenv("DATEMSK") != 0)
		return 1;
	if(getdate(date) != NULL)
		return 1;
	if(getdate_err != 1)
		return 1;
	return 0;
}


/* mktime */
static int _mktime(char const * progname)
{
	time_t t = 0;
	struct tm tm;

	printf("%s: Testing mktime()\n", progname);
	tzset();
	if(localtime_r(&t, &tm) == NULL)
		return -1;
	if((t = mktime(&tm)) == (time_t)-1
			|| t != 0)
		return -1;
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int res = 0;

	res += _clock(argv[0]);
	res += _getdate(argv[0]);
	res += _mktime(argv[0]);
	return (res == 0) ? 0 : 2;
}
