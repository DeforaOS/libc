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



#include <fcntl.h>
#include <stdio.h>
#include "../src/stdio.c"


/* stdio */
static int _stdio(char const * progname, char const * mode, int expected)
{
	int m = _fopen_mode(mode);

	printf("%s: Testing fopen() mode \"%s\": 0x%x (0x%x)\n", progname,
			mode, m, expected);
	return (m == expected) ? 0 : 1;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _stdio(argv[0], "a", O_WRONLY | O_APPEND | O_CREAT);
	ret += _stdio(argv[0], "ab", O_WRONLY | O_APPEND | O_CREAT);
	ret += _stdio(argv[0], "a+", O_RDWR | O_APPEND | O_CREAT);
	ret += _stdio(argv[0], "ab+", O_RDWR | O_APPEND | O_CREAT);
	ret += _stdio(argv[0], "ax", O_WRONLY | O_APPEND | O_CREAT | O_EXCL);
	ret += _stdio(argv[0], "abx", O_WRONLY | O_APPEND | O_CREAT | O_EXCL);
	ret += _stdio(argv[0], "a+x", O_RDWR | O_APPEND | O_CREAT | O_EXCL);
	ret += _stdio(argv[0], "ab+x", O_RDWR | O_APPEND | O_CREAT | O_EXCL);
	ret += _stdio(argv[0], "r", O_RDONLY);
	ret += _stdio(argv[0], "rb", O_RDONLY);
	ret += _stdio(argv[0], "r+", O_RDWR);
	ret += _stdio(argv[0], "rb+", O_RDWR);
	ret += _stdio(argv[0], "rx", O_RDONLY | O_EXCL);
	ret += _stdio(argv[0], "rbx", O_RDONLY | O_EXCL);
	ret += _stdio(argv[0], "r+x", O_RDWR | O_EXCL);
	ret += _stdio(argv[0], "rb+x", O_RDWR | O_EXCL);
	ret += _stdio(argv[0], "w", O_WRONLY | O_TRUNC | O_CREAT);
	ret += _stdio(argv[0], "wb", O_WRONLY | O_TRUNC | O_CREAT);
	ret += _stdio(argv[0], "w+", O_RDWR | O_TRUNC | O_CREAT);
	ret += _stdio(argv[0], "wb+", O_RDWR | O_TRUNC | O_CREAT);
	ret += _stdio(argv[0], "wx", O_WRONLY | O_TRUNC | O_CREAT | O_EXCL);
	ret += _stdio(argv[0], "wbx", O_WRONLY | O_TRUNC | O_CREAT | O_EXCL);
	ret += _stdio(argv[0], "w+x", O_RDWR | O_TRUNC | O_CREAT | O_EXCL);
	ret += _stdio(argv[0], "wb+x", O_RDWR | O_TRUNC | O_CREAT | O_EXCL);
	return (ret == 0) ? 0 : 2;
}
