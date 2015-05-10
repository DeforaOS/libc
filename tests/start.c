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



#include <stdio.h>
#include <string.h>
extern char ** environ;


/* usage */
static int _usage(void)
{
	fputs("Usage: start arg1 arg2\n", stderr);
	return 1;
}


/* main */
int main(int argc, char * argv[], char * envp[])
{
	int ret = 0;
	size_t len;
	int i;
	char const * sep;

	if(argc != 3)
		return _usage();
	printf("%s: %s\n", argv[0], "Testing arguments:");
	if(argv == NULL)
		ret |= 1;
	else if((len = strlen(argv[0])) < 6
			|| strcmp(&argv[0][len - 6], "/start") != 0)
		ret |= 2;
	else if(strcmp(argv[1], "argv1") != 0)
		ret |= 4;
	else if(strcmp(argv[2], "argv2") != 0)
		ret |= 8;
	else if(argv[3] != NULL)
		ret |= 16;
	else
	{
		for(i = 0, sep = ""; i < argc; i++)
		{
			printf("%s%d: %s", sep, i, argv[i]);
			sep = ", ";
		}
		putchar('\n');
	}
	printf("%s: %s\n", argv[0], "Testing the environment");
	if(envp == NULL || environ == NULL)
		ret |= 32;
	else
		for(i = 0; envp[i] != NULL && environ[i] != NULL; i++)
			if(strcmp(envp[i], environ[i]) != 0)
				ret |= 64;
	return ret;
}
