/* $Id$ */
/* Copyright (c) 2014 Pierre Pronchery <khorben@defora.org> */
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
#include "../src/stdlib.c"


/* stdlib */
/* private */
/* prototypes */
static int _mkstemp(char const * progname);
static int _mktemp(char const * progname);


/* functions */
/* mkstemp */
static int _mkstemp(char const * progname)
{
	int ret = 0;
	char buf[] = "/tmp/stdlib.XXXXXX";
	int fd;

	printf("%s: Testing mkstemp()\n", progname);
	if((fd = mkstemp(buf)) < 0)
		return 1;
	if(unlink(buf) != 0)
		ret = 1;
	if(close(fd) != 0)
		ret = 1;
	return ret;
}


/* mktemp */
static int _mktemp(char const * progname)
{
	char buf[] = "/tmp/stdlib.XXXXXX";

	printf("%s: Testing mktemp()\n", progname);
	return (mktemp(buf) == buf) ? 0 : 1;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _mkstemp(argv[0]);
	ret += _mktemp(argv[0]);
	return (ret == 0) ? 0 : 2;
}
