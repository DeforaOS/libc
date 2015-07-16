/* $Id$ */
/* Copyright (c) 2012-2014 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/resource.h>
#include <stdio.h>


/* resource */
/* error */
static int _error(char const * message, int ret)
{
	fputs("resource: ", stderr);
	perror(message);
	return ret;
}


/* main */
int main(void)
{
	int ret = 0;
	int limits[] =
	{
#ifdef RLIMIT_CPU
		RLIMIT_CPU,
#endif
#ifdef RLIMIT_FSIZE
		RLIMIT_FSIZE,
#endif
#ifdef RLIMIT_DATA
		RLIMIT_DATA,
#endif
#ifdef RLIMIT_STACK
		RLIMIT_STACK,
#endif
#ifdef RLIMIT_CORE
		RLIMIT_CORE,
#endif
#ifdef RLIMIT_RSS
		RLIMIT_RSS,
#endif
#ifdef RLIMIT_MEMLOCK
		RLIMIT_MEMLOCK,
#endif
#ifdef RLIMIT_NPROC
		RLIMIT_NPROC,
#endif
#ifdef RLIMIT_NOFILE
		RLIMIT_NOFILE,
#endif
#ifdef RLIMIT_AS
		RLIMIT_AS,
#endif
		-1
	};
	size_t i;
	struct rlimit rl;

	for(i = 0; limits[i] != -1; i++)
	{
		if(getrlimit(limits[i], &rl) != 0)
		{
			ret |= _error("getrlimit", 2);
			continue;
		}
		printf("%d: %lld (%lld)\n", limits[i], rl.rlim_cur,
				rl.rlim_max);
		if(setrlimit(limits[i], &rl) != 0)
			ret |= _error("setrlimit", 3);
	}
	if(i == 0)
		/* at least one value should be supported */
		ret = 4;
	return ret;
}
