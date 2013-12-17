/* $Id$ */
/* Copyright (c) 2013 Pierre Pronchery <khorben@defora.org> */
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



#include <stdio.h>
#include <string.h>
#include <stdarg.h>


/* stdarg */
static int _stdarg_int(char const * progname, ...);
static char const * _stdarg_str(char const * progname, ...);

static int _stdarg(char const * progname)
{
	int ret = 0;
	const int i = 37;
	char const str[] = "Just a simple string.";

	printf("%s: Testing va_arg()\n", progname);
	if(_stdarg_int(progname, i) != i)
		ret += 1;
	if(strcmp(_stdarg_str(progname, str), str) != 0)
		ret += 1;
	return ret;
}

static int _stdarg_int(char const * progname, ...)
{
	int ret;
	va_list ap;

	va_start(ap, progname);
	ret = va_arg(ap, int);
	va_end(ap);
	return ret;
}

static char const * _stdarg_str(char const * progname, ...)
{
	char const * ret;
	va_list ap;

	va_start(ap, progname);
	ret = va_arg(ap, char const *);
	va_end(ap);
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _stdarg(argv[0]);
	return (ret == 0) ? 0 : 2;
}
