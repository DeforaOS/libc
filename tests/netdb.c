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
#include <netdb.h>


/* prototypes */
static int _netdb(char const * progname);
static void _hstrerror(char const * progname, char const * message, int value);


/* functions */
/* netdb */
static int _netdb(char const * progname)
{
	struct hostent * he;

	/* gethostent */
	while((he = gethostent()) != NULL)
		printf("%s\n", he->h_name);
	/* hstrerror */
	_hstrerror(progname, "HOST_NOT_FOUND", HOST_NOT_FOUND);
	_hstrerror(progname, "TRY_AGAIN", TRY_AGAIN);
	_hstrerror(progname, "NO_RECOVERY", NO_RECOVERY);
	_hstrerror(progname, "NO_DATA", NO_DATA);
	return 0;
}


/* hstrerror */
static void _hstrerror(char const * progname, char const * message, int value)
{
	printf("%s: %s: %s\n", progname, message, hstrerror(value));
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret |= _netdb(argv[0]);
	return (ret == 0) ? 0 : 2;
}
