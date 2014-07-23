/* $Id$ */
/* Copyright (c) 2012-2014 Pierre Pronchery <khorben@defora.org> */
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



#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include "../src/stdio.c"


/* stdio */
/* fopen */
static int _fopen(char const * progname, char const * mode, int expected)
{
	int m = _fopen_mode(mode);

	printf("%s: Testing fopen() mode \"%s\": 0x%x (0x%x)\n", progname,
			mode, m, expected);
	return (m == expected) ? 0 : 1;
}


/* sscanf */
static int _sscanf(char const * progname)
{
	char const * str = "abc   e 42def3";
	char const * format = "abc e %udef%c";
	unsigned int u;
	char c;
	char buf[4];

	printf("%s: Testing sscanf()\n", progname);
	if(sscanf(str, format, &u, &c) != 2
			|| u != 42 || c != '3')
		return 1;
	if(sscanf(str, "%3s", &buf) != 1
			|| strncmp(str, buf, 3) != 0)
		return 2;
	return 0;
}


/* tmpfile */
static int _tmpfile(char const * progname)
{
	FILE * fp;

	printf("%s: Testing tmpfile()\n", progname);
	if((fp = tmpfile()) == NULL)
		return 1;
	fclose(fp);
	return 0;
}


/* tmpnam */
static int _tmpnam(char const * progname, char * str)
{
	printf("%s: Testing tmpnam()\n", progname);
	return (tmpnam(str) != NULL) ? 0 : 1;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _fopen(argv[0], "a", O_WRONLY | O_APPEND | O_CREAT);
	ret += _fopen(argv[0], "ab", O_WRONLY | O_APPEND | O_CREAT);
	ret += _fopen(argv[0], "a+", O_RDWR | O_APPEND | O_CREAT);
	ret += _fopen(argv[0], "ab+", O_RDWR | O_APPEND | O_CREAT);
	ret += _fopen(argv[0], "ax", O_WRONLY | O_APPEND | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "abx", O_WRONLY | O_APPEND | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "a+x", O_RDWR | O_APPEND | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "ab+x", O_RDWR | O_APPEND | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "r", O_RDONLY);
	ret += _fopen(argv[0], "rb", O_RDONLY);
	ret += _fopen(argv[0], "r+", O_RDWR);
	ret += _fopen(argv[0], "rb+", O_RDWR);
	ret += _fopen(argv[0], "rx", O_RDONLY | O_EXCL);
	ret += _fopen(argv[0], "rbx", O_RDONLY | O_EXCL);
	ret += _fopen(argv[0], "r+x", O_RDWR | O_EXCL);
	ret += _fopen(argv[0], "rb+x", O_RDWR | O_EXCL);
	ret += _fopen(argv[0], "w", O_WRONLY | O_TRUNC | O_CREAT);
	ret += _fopen(argv[0], "wb", O_WRONLY | O_TRUNC | O_CREAT);
	ret += _fopen(argv[0], "w+", O_RDWR | O_TRUNC | O_CREAT);
	ret += _fopen(argv[0], "wb+", O_RDWR | O_TRUNC | O_CREAT);
	ret += _fopen(argv[0], "wx", O_WRONLY | O_TRUNC | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "wbx", O_WRONLY | O_TRUNC | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "w+x", O_RDWR | O_TRUNC | O_CREAT | O_EXCL);
	ret += _fopen(argv[0], "wb+x", O_RDWR | O_TRUNC | O_CREAT | O_EXCL);
	ret += _sscanf(argv[0]);
	ret += _tmpfile(argv[0]);
	ret += _tmpnam(argv[0], NULL);
	return (ret == 0) ? 0 : 2;
}
