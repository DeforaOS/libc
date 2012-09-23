/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
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



#include <regex.h>
#include <stdio.h>


/* regex */
static void _regex(char const * progname)
{
	int error[] =
	{
		REG_NOMATCH, REG_BADPAT, REG_ECOLLATE, REG_ECTYPE, REG_EESCAPE,
		REG_ESUBREG, REG_EBRACK, REG_EPAREN, REG_EBRACE, REG_BADBR,
		REG_ERANGE, REG_ESPACE, REG_BADRPT
	};
	char buf[80];
	size_t size;
	size_t i;

	for(i = 0; i < sizeof(error) / sizeof(*error); i++)
	{
		size = regerror(error[i], NULL, buf, sizeof(buf));
		printf("%s: Testing %s: % 2u \"%s\" (%lu)\n", progname,
				"regerror()", error[i], buf, size);
	}
}


/* main */
int main(int argc, char * argv[])
{
	_regex(argv[0]);
	return 0;
}
