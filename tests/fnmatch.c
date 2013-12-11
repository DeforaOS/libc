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
#include <fnmatch.h>


/* fnmatch */
static int _fnmatch(char const * progname)
{
	int ret = 0;
	const int flags = 0;

	printf("%s: Testing fnmatch()\n", progname);
	ret += (fnmatch("", "", flags) == 0) ? 0 : 1;
	ret += (fnmatch("a", "a", flags) == 0) ? 0 : 1;
	ret += (fnmatch("a", "b", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("?", "a", flags) == 0) ? 0 : 1;
	ret += (fnmatch("?a", "ba", flags) == 0) ? 0 : 1;
	ret += (fnmatch("?a", "ab", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("a?", "ab", flags) == 0) ? 0 : 1;
	ret += (fnmatch("a?a", "aba", flags) == 0) ? 0 : 1;
	ret += (fnmatch("b?b", "aba", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("*", "aaa", flags) == 0) ? 0 : 1;
	ret += (fnmatch("a*", "abbb", flags) == 0) ? 0 : 1;
	ret += (fnmatch("a*b", "abbba", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("*a", "bbba", flags) == 0) ? 0 : 1;
	ret += (fnmatch("*b", "bbba", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("*.c", "fnmatch.c", flags) == 0) ? 0 : 1;
	ret += (fnmatch("*.h", "fnmatch.c", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("*b*", "bbbab", flags) == 0) ? 0 : 1;
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _fnmatch(argv[0]);
	return (ret == 0) ? 0 : 2;
}
