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



#include <string.h>
#include <stdio.h>
#include <errno.h>


/* memchr */
static int _memchr(char const * progname)
{
	int ret = 0;
	char const search[] = "sear\xff\xfe\x7f\x7e\x00\x01ch";
	size_t i;
	void * p;

	printf("%s: Testing %s\n", progname, "memchr()");
	for(i = 0; i < sizeof(search); i++)
	{
		p = memchr(search, search[i], sizeof(search));
		if(p == NULL || strcmp(p, &search[i]) != 0)
			ret += 1;
	}
	ret += memchr(search, 'z', sizeof(search)) == NULL ? 0 : 1;
	return ret;
}


/* strerror */
static void _strerror(char const * progname)
{
	int errors[] =
	{
		0,
		E2BIG,
		EACCES,
		EAGAIN,
		EBADF,
		EBUSY,
		ECHILD,
#ifdef EDOM
		EDOM,
#endif
		EEXIST,
		EFAULT,
		EINTR,
		EINVAL,
		EIO,
		EISDIR,
		ENODEV,
		ENOENT,
		ENOEXEC,
		ENOMEM,
#ifdef ENOSPC
		ENOSPC,
#endif
		ENOSYS,
		ENOTDIR,
		ENOTSUP,
		ENOTTY,
		ENXIO,
		EPERM,
		EPIPE,
		ERANGE,
		EROFS,
#ifdef ESPIPE
		ESPIPE,
#endif
#ifdef ESRCH
		ESRCH,
#endif
		ETIMEDOUT,
		EXDEV
	};
	size_t i;

	for(i = 0; i < sizeof(errors) / sizeof(*errors); i++)
		printf("%s: Testing %s: \"%s\" (%u)\n", progname,
				"strerror()", strerror(errors[i]), errors[i]);
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _memchr(argv[0]);
	_strerror(argv[0]);
	return (ret == 0) ? 0 : 2;
}
