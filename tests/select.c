/* $Id$ */
/* Copyright (c) 2012-2013 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/select.h>
#include <stdio.h>
#include <time.h>


/* pselect */
static int _pselect(char const * progname)
{
	int ret = 0;
	fd_set rfds;
	fd_set wfds;
	fd_set efds;
	struct timespec timeout;

	printf("%s: Testing %s()\n", progname, "pselect");
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_ZERO(&efds);
	timeout.tv_sec = 0;
	timeout.tv_nsec = 0;
	if(pselect(0, &rfds, &wfds, &efds, &timeout, NULL) != 0)
		ret = 2;
	return ret;
}


/* pselect2 */
static int _pselect2(char const * progname, unsigned int t)
{
	struct timespec timeout;
	time_t before;
	time_t after;

	printf("%s: Testing %s() (sleeping %us)\n", progname, "pselect2", t);
	timeout.tv_sec = t;
	timeout.tv_nsec = 0;
	before = time(NULL);
	if(pselect(0, NULL, NULL, NULL, &timeout, NULL) != 0)
		return 2;
	after = time(NULL);
	return (after - before == t) ? 0 : 2;
}


/* select */
static int _select(char const * progname)
{
	int ret = 0;
	fd_set rfds;
	fd_set wfds;
	fd_set efds;
	struct timeval timeout;

	printf("%s: Testing %s()\n", progname, "select");
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_ZERO(&efds);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	if(select(0, &rfds, &wfds, &efds, &timeout) != 0)
		ret = 2;
	return ret;
}


/* select2 */
static int _select2(char const * progname, unsigned int t)
{
	struct timeval timeout;
	time_t before;
	time_t after;

	printf("%s: Testing %s() (sleeping %us)\n", progname, "select", t);
	timeout.tv_sec = t;
	timeout.tv_usec = 0;
	before = time(NULL);
	if(select(0, NULL, NULL, NULL, &timeout) != 0)
		return 2;
	after = time(NULL);
	return (after - before == t) ? 0 : 2;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret |= _pselect(argv[0]);
	ret |= _pselect2(argv[0], 0);
	ret |= _pselect2(argv[0], 1);
	ret |= _select(argv[0]);
	ret |= _select2(argv[0], 0);
	ret |= _select2(argv[0], 1);
	return (ret == 0) ? 0 : 2;
}
