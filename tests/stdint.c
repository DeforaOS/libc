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



#include <stdint.h>
#include <stdio.h>


/* stdint */
static int _stdint(char const * progname, size_t size, char const * name,
		size_t expected)
{
	int ret = 0;
	char const * message = "";

	if(size != expected)
	{
		ret = 1;
		message = "FAILED";
	}
	printf("%s: Testing %s: %u (%u)%s\n", progname, name, size, expected,
			message);
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret |= _stdint(argv[0], sizeof(int8_t), "int8_t", 1);
	ret |= _stdint(argv[0], sizeof(int16_t), "int16_t", 2);
	ret |= _stdint(argv[0], sizeof(int32_t), "int32_t", 4);
	ret |= _stdint(argv[0], sizeof(int64_t), "int64_t", 8);
	ret |= _stdint(argv[0], sizeof(uint8_t), "uint8_t", 1);
	ret |= _stdint(argv[0], sizeof(uint16_t), "uint16_t", 2);
	ret |= _stdint(argv[0], sizeof(uint32_t), "uint32_t", 4);
	ret |= _stdint(argv[0], sizeof(uint64_t), "uint64_t", 8);
	return (ret == 0) ? 0 : 2;
}
