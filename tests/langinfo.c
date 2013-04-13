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
#include <langinfo.h>


/* langinfo */
static int _langinfo(char const * progname, nl_item item)
{
	printf("%s: nl_langinfo(%lu) returns %s\n", progname,
			nl_langinfo(item));
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int res = 0;

	res += _langinfo(argv[0], CODESET);
	return (res == 0) ? 0 : 2;
}
