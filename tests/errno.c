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
#include <errno.h>


/* errno */
static int _errno(char const * progname)
{
	printf("%s: Testing errno\n", progname);
	printf("%d\n", errno);
	errno = 17;
	printf("%d\n", errno);
	return (errno == 17) ? 0 : 2;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _errno(argv[0]);
	return (ret == 0) ? 0 : 2;
}
