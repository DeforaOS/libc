/* $Id$ */
/* Copyright (c) 2014-2015 Pierre Pronchery <khorben@defora.org> */
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



#include <stdio.h>
#include <stdlib.h>
#include "../src/stdlib.c"


/* stdlib */
/* private */
/* prototypes */
static int _error(char const * progname, char const * message, int ret);

static int _mkstemp(char const * progname);
static int _mktemp(char const * progname);
static int _strtod(char const * progname, char const * str, double expected);


/* functions */
/* error */
static int _error(char const * progname, char const * message, int ret)
{
	fputs(progname, stderr);
	fputs(": ", stderr);
	perror(message);
	return ret;
}


/* mkstemp */
static int _mkstemp(char const * progname)
{
	int ret = 0;
	char buf[] = "/tmp/stdlib.XXXXXX";
	int fd;

	printf("%s: Testing mkstemp()\n", progname);
	if((fd = mkstemp(buf)) < 0)
		return _error(progname, "mkstemp", 1);
	if(unlink(buf) != 0)
		ret = _error(progname, "unlink", 1);
	if(close(fd) != 0)
		ret = _error(progname, "close", 1);
	return ret;
}


/* mktemp */
static int _mktemp(char const * progname)
{
	char buf[] = "/tmp/stdlib.XXXXXX";

	printf("%s: Testing mktemp()\n", progname);
	return (mktemp(buf) == buf) ? 0 : _error(progname, "mktemp", 1);
}


/* strtod */
static int _strtod(char const * progname, char const * str, double expected)
{
	double d;
	char * p;

	printf("%s: Testing strtod(\"%s\", %f)\n", progname, str, expected);
	d = strtod(str, &p);
	return (d == expected && *p == '\0') ? 0 : 1;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _mkstemp(argv[0]);
	ret += _mktemp(argv[0]);
	ret += _strtod(argv[0], "0.0", 0.0);
	return (ret == 0) ? 0 : 2;
}
