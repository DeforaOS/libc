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



#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>


/* socket */
static int _socket(char const * progname, char const * title, int type)
{
	int fd;

	printf("%s: Testing %s(%s)\n", progname, "socket", title);
	if((fd = socket(AF_INET, type, 0)) < 0)
		return 2;
	if(close(fd) != 0)
		return 2;
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret |= _socket(argv[0], "1/2", SOCK_DGRAM);
	ret |= _socket(argv[0], "2/2", SOCK_STREAM);
	return (ret == 0) ? 0 : 2;
}
