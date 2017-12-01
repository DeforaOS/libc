/* $Id$ */
/* Copyright (c) 2013-2015 Pierre Pronchery <khorben@defora.org> */
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
#include <string.h>
#include <stdarg.h>


/* stdarg */
static int _stdarg_error(char const * progname, char const * type);
static int _stdarg_int(char const * progname, ...);
static char const * _stdarg_str(char const * progname, ...);

static int _stdarg(char const * progname)
{
	int ret = 0;
	const int i = 37;
	char const str[] = "Just a simple string.";

	printf("%s: Testing va_arg()\n", progname);
	if(_stdarg_int(progname, i) != i)
		ret += _stdarg_error(progname, "int");
	if(strcmp(_stdarg_str(progname, str), str) != 0)
		ret += _stdarg_error(progname, "char const *");
	return ret;
}

static int _stdarg_error(char const * progname, char const * type)
{
	fprintf(stderr, "%s: %s: %s\n", progname, type, "Did not match");
	return 1;
}

static int _stdarg_int(char const * progname, ...)
{
	int ret;
	va_list ap;

	va_start(ap, progname);
	ret = va_arg(ap, int);
	va_end(ap);
	return ret;
}

static char const * _stdarg_str(char const * progname, ...)
{
	char const * ret;
	va_list ap;

	va_start(ap, progname);
	ret = va_arg(ap, char const *);
	va_end(ap);
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret += _stdarg(argv[0]);
	return (ret == 0) ? 0 : 2;
}
