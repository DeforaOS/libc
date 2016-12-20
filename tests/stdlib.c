/* $Id$ */
/* Copyright (c) 2014-2016 Pierre Pronchery <khorben@defora.org> */
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



#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>


/* stdlib */
/* private */
/* prototypes */
static int _error(char const * progname, char const * message, int ret);

static int _arc4random(char const * progname);
static int _mkstemp(char const * progname);
static int _mktemp(char const * progname);
static int _strtold(char const * progname, char const * str,
		long double expected);
static int _strtol(char const * progname);
static int _strtoul(char const * progname);


/* functions */
/* arc4random */
static int _arc4random(char const * progname)
{
	uint32_t res[4];
	size_t i;

	printf("%s: Testing arc4random()\n", progname);
	for(i = 0; i < sizeof(res) / sizeof(*res); i++)
		res[i] = arc4random();
	for(i = 0; i < sizeof(res) / sizeof(*res); i++)
		printf("%u. 0x%08x\n", i + 1, res[i]);
	/* XXX false negatives are unlikely but possible */
	for(i = 1; i < sizeof(res) / sizeof(*res); i++)
		if(res[i] == res[0])
			return 1;
	return 0;
}


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


/* strtold */
static int _strtold(char const * progname, char const * str,
		long double expected)
{
	int ret = 0;
	long double ld;
	double d;
	float f;
	char * p;

	printf("%s: Testing strtold(\"%s\", %f)\n", progname, str, expected);
	ld = strtold(str, &p);
	if(ld != expected || *p != '\0')
	{
		fprintf(stderr, "%s: %s: Obtained %f (expected: %f)\n",
				progname, "strtold", ld, expected);
		ret = 1;
	}
	printf("%s: Testing strtod(\"%s\", %f)\n", progname, str, expected);
	d = strtod(str, &p);
	if(d != (double)expected || *p != '\0')
	{
		fprintf(stderr, "%s: %s: Obtained %f (expected: %f)\n",
				progname, "strtod", d, expected);
		ret = 1;
	}
	printf("%s: Testing strtof(\"%s\", %f)\n", progname, str, expected);
	f = strtof(str, &p);
	if(f != (float)expected || *p != '\0')
	{
		fprintf(stderr, "%s: %s: Obtained %f (expected: %f)\n",
				progname, "strtof", f, expected);
		ret = 1;
	}
	return ret;
}


/* strtol */
static int _strtol(char const * progname)
{
	char * p;
	char const spaces[] = "      ";
	unsigned long lu;
	char buf[32];

	/* spaces */
	errno = 0;
	strtol(spaces, &p, 0);
	if(p != spaces || errno != ERANGE)
	{
		fprintf(stderr, "%s: %s: Conversion error (spaces)\n", progname,
				"strtol");
		return 1;
	}
	/* -(LONG_MAX + 1) */
	lu = LONG_MAX + 1;
	snprintf(buf, sizeof(buf), "-%lu", lu);
	errno = 0;
	strtol(buf, &p, 10);
	if(errno != ERANGE)
	{
		fprintf(stderr, "%s: %s: Conversion error (-(LONG_MAX + 1))\n",
				progname, "strtol");
		return 1;
	}
	return 0;
}


/* strtoul */
static int _strtoul(char const * progname)
{
	char * p;
	char const spaces[] = "      ";
	char buf[32];

	/* spaces */
	errno = 0;
	strtoul(spaces, &p, 0);
	if(p != spaces || errno != ERANGE)
	{
		fprintf(stderr, "%s: %s: Conversion error (spaces)\n", progname,
				"strtoul");
		return 1;
	}
	/* ULONG_MAX */
	snprintf(buf, sizeof(buf), "%lu", ULONG_MAX);
	errno = 0;
	strtoul(buf, &p, 10);
	if(errno != 0 || *p != '\0')
	{
		fprintf(stderr, "%s: %s: Conversion error (ULONG_MAX)\n",
				progname, "strtoul");
		return 1;
	}
	return 0;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _arc4random(argv[0]);
	ret += _mkstemp(argv[0]);
	ret += _mktemp(argv[0]);
	ret += _strtold(argv[0], "0.0", 0.0);
	ret += _strtold(argv[0], "0.1", 0.1);
	ret += _strtold(argv[0], "1.0", 1.0);
	ret += _strtold(argv[0], "1.1", 1.1);
	ret += _strtold(argv[0], "1.01", 1.01);
	ret += _strtold(argv[0], "-1.1", -1.1);
	ret += _strtold(argv[0], "-1.01", -1.01);
	ret += _strtol(argv[0]);
	ret += _strtoul(argv[0]);
	return (ret == 0) ? 0 : 2;
}
