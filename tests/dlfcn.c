/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
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



#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "../src/dl/dlfcn.c"


/* dlfcn */
/* private */
/* functions */
static int _dlfcn(char const * progname, char const * title,
		char const * soname)
{
	int ret = 0;
	void * handle;
	int * p;
	pid_t (*g)(void);

	printf("%s: Testing %s\n", progname, title);
	if((handle = dlopen(soname, RTLD_LAZY)) == NULL)
	{
		printf("%s: %s\n", progname, dlerror());
		return -1;
	}
	/* checking the value of a known variable */
	printf("%s: Testing %s, %s\n", progname, title, "dlsym() (1/2)");
	if((p = dlsym(handle, "errno")) == NULL)
	{
		printf("%s: %s\n", progname, dlerror());
		ret++;
	}
	else if((soname != NULL && *p != 0)
			|| (soname == NULL && p != &errno))
	{
		printf("%s: errno: Wrong value\n", progname);
		ret++;
	}
	/* calling a simple syscall */
	printf("%s: Testing %s, %s\n", progname, title, "dlsym() (2/2)");
	if((g = dlsym(handle, "getpid")) == NULL)
	{
		printf("%s: %s\n", progname, dlerror());
		ret++;
	}
	else if((soname != NULL && getpid() != g())
				|| (soname == NULL && getpid != (void *)p))
	{
		printf("%s: getpid(): Wrong value\n", progname);
		ret++;
	}
	dlclose(handle);
	return ret;
}


/* public */
/* functions */
int main(int argc, char * argv[])
{
	int ret = 0;
	char const * soname = argv[0];

	if(argc == 2)
		soname = argv[1];
	ret |= _dlfcn(argv[0], "dlopen() (1/2)", soname);
	ret |= _dlfcn(argv[0], "dlopen() (2/2)", NULL);
	return (ret == 0) ? 0 : 2;
}
