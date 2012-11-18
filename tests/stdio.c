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



#include <stdio.h>
#include "../src/stdio.c"


/* stdio */
static int _stdio(char const * progname, char const * mode)
{
	int m = _fopen_mode(mode);

	printf("%s: Testing fopen() mode \"%s\": 0x%x\n", progname, mode, m);
	return (m != -1) ? 0 : 1;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _stdio(argv[0], "r");
	ret += _stdio(argv[0], "rb");
	ret += _stdio(argv[0], "r+");
	ret += _stdio(argv[0], "rb+");
	ret += _stdio(argv[0], "rx");
	ret += _stdio(argv[0], "rbx");
	ret += _stdio(argv[0], "r+x");
	ret += _stdio(argv[0], "rb+x");
	ret += _stdio(argv[0], "w");
	ret += _stdio(argv[0], "wb");
	ret += _stdio(argv[0], "w+");
	ret += _stdio(argv[0], "wb+");
	ret += _stdio(argv[0], "wx");
	ret += _stdio(argv[0], "wbx");
	ret += _stdio(argv[0], "w+x");
	ret += _stdio(argv[0], "wb+x");
	return (ret == 0) ? 0 : 2;
}
