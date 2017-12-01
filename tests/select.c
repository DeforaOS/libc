/* $Id$ */
/* Copyright (c) 2012-2013 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#include <sys/select.h>
#include <stdio.h>
#include <time.h>


/* prototypes */
static int _pselect(char const * progname);
static int _pselect2(char const * progname, unsigned int t);
static int _select(char const * progname);
static int _select2(char const * progname, unsigned int t);
static int _error(char const * progname, char const * message, int ret);


/* functions */
/* pselect */
static int _pselect(char const * progname)
{
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
		return _error(progname, "pselect", 2);
	return 0;
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
		return _error(progname, "pselect", 2);
	after = time(NULL);
	return (after - before == t) ? 0 : 2;
}


/* select */
static int _select(char const * progname)
{
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
		return _error(progname, "select", 2);
	return 0;
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
		return _error(progname, "select", 2);
	after = time(NULL);
	return (after - before == t) ? 0 : 2;
}


/* error */
static int _error(char const * progname, char const * message, int ret)
{
	fprintf(stderr, "%s: ", progname);
	perror(message);
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret |= _pselect(argv[0]);
	ret |= _pselect2(argv[0], 0);
	ret |= _pselect2(argv[0], 1);
	ret |= _select(argv[0]);
	ret |= _select2(argv[0], 0);
	ret |= _select2(argv[0], 1);
	return (ret == 0) ? 0 : 2;
}
