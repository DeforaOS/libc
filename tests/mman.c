/* $Id$ */
/* Copyright (c) 2016 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>


/* mman */
/* private */
/* prototypes */
static int _mman(char const * progname);

static int _error(char const * progname, char const * message, int ret);


/* functions */
/* mman */
static int _mman(char const * progname)
{
	int ret = 0;
	char * addr;
	size_t i;

	if((addr = mmap(NULL, PAGE_SIZE, PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE,
					-1, 0)) == MAP_FAILED)
		return _error(progname, "mmap", 1);
	for(i = 0; i < PAGE_SIZE; i++)
		if(addr[i] != '\0')
		{
			/* XXX report errors */
			ret = 1;
			break;
		}
	if(munmap(addr, PAGE_SIZE) != 0)
		return _error(progname, "munmap", 1);
	return ret;
}


/* error */
static int _error(char const * progname, char const * message, int ret)
{
	fputs(progname, stderr);
	fputs(": ", stderr);
	perror(message);
	return ret;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _mman(argv[0]);
	return (ret == 0) ? 0 : 2;
}
