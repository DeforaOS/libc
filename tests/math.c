/* $Id$ */
/* Copyright (c) 2017 Pierre Pronchery <khorben@defora.org> */
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
#include <stdarg.h>
#include <stdio.h>
#include <math.h>


/* math */
/* private */
/* prototypes */
static int _math(char const * progname);

static int _error(int code, char const * format, ...);


/* functions */
/* math */
static int _math(char const * progname)
{
	int ret = 0;

	if(cos(0.0) != 1.0 || cosl(0.0) != 1.0)
		ret |= _error(2, "%s: cos(): Wrong value", progname);
	if(sin(0.0) != 0.0 || sinl(0.0) != 0.0)
		ret |= _error(2, "%s: sin(): Wrong value", progname);
	if(fabs(-3.0) != 3.0 || fabsf(-3.0) != 3.0 || fabsl(-3.0) != 3.0)
		ret |= _error(4, "%s: fabs(): Wrong value", progname);
	if(fmod(11, 7) != 4 || fmodl(11, 7) != 4)
		ret |= _error(8, "%s: fmod(): Wrong value", progname);
	if(pow(3.0, 0.0) != 1.0 || pow(4.0, 1.0) != 4.0 || pow(2.0, 3.0) != 8.0)
		ret |= _error(16, "%s: pow(): Wrong value", progname);
	if(round(1.5) != 2.0)
		ret |= _error(32, "%s: round(): Wrong value", progname);
	if(sqrt(4.0) != 2.0)
		ret |= _error(64, "%s: sqrt(): Wrong value", progname);
	return ret;
}


/* error */
static int _error(int code, char const * format, ...)
{
	va_list ap;

	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
	putchar('\n');
	return code;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret |= _math(argv[0]);
	return (ret == 0) ? 0 : 2;
}
