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
#include <math.h>


/* math */
/* private */
/* functions */
static int _math(char const * progname)
{
	int ret = 0;

	if(cos(0.0) != 1.0
			|| sin(0.0) != 0.0
			|| cosl(0.0) != 1.0
			|| sinl(0.0) != 0.0)
		ret |= 2;
	if(fabs(-3.0) != 3.0
			|| fabsf(-3.0) != 3.0
			|| fabsl(-3.0) != 3.0)
		ret |= 4;
	if(fmod(11, 7) != 4
			|| fmodl(11, 7) != 4)
		ret |= 8;
	if(round(1.5) != 2.0)
		ret |= 16;
	if(sqrt(4.0) != 2.0)
		ret |= 32;
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret |= _math(argv[0]);
	return (ret == 0) ? 0 : 2;
}
