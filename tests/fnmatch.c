/* $Id$ */
/* Copyright (c) 2013 Pierre Pronchery <khorben@defora.org> */
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
#include <fnmatch.h>


/* fnmatch */
static int _fnmatch(char const * progname)
{
	int ret = 0;
	const int flags = 0;

	printf("%s: Testing fnmatch()\n", progname);
	ret += (fnmatch("", "", flags) == 0) ? 0 : 1;
	ret += (fnmatch("a", "a", flags) == 0) ? 0 : 1;
	ret += (fnmatch("a", "b", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("?", "a", flags) == 0) ? 0 : 1;
	ret += (fnmatch("?a", "ba", flags) == 0) ? 0 : 1;
	ret += (fnmatch("?a", "ab", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("a?", "ab", flags) == 0) ? 0 : 1;
	ret += (fnmatch("a?a", "aba", flags) == 0) ? 0 : 1;
	ret += (fnmatch("b?b", "aba", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("*", "aaa", flags) == 0) ? 0 : 1;
	ret += (fnmatch("a*", "abbb", flags) == 0) ? 0 : 1;
	ret += (fnmatch("a*b", "abbba", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("*a", "bbba", flags) == 0) ? 0 : 1;
	ret += (fnmatch("*b", "bbba", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("*.c", "fnmatch.c", flags) == 0) ? 0 : 1;
	ret += (fnmatch("*.h", "fnmatch.c", flags) == FNM_NOMATCH) ? 0 : 1;
	ret += (fnmatch("*b*", "bbbab", flags) == 0) ? 0 : 1;
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret += _fnmatch(argv[0]);
	return (ret == 0) ? 0 : 2;
}
