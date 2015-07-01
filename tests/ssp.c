/* $Id$ */
/* Copyright (c) 2015 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>


/* private */
/* prototypes */
static int _ssp(char const * progname, unsigned int pattern);

static int _error(char const * progname, char const * message, int ret);


/* functions */
/* ssp */
static int _ssp_child(char const * progname, unsigned int pattern);
/* XXX do not make it static as the compiler may optimize it inline */
void _ssp_child_sub(char const * progname, unsigned int pattern);

static int _ssp(char const * progname, unsigned int pattern)
{
	pid_t pid;
	int status;

	if((pid = fork()) == -1)
		return -_error(progname, "fork", 1);
	if(pid == 0)
		return -_ssp_child(progname, pattern);
	while(waitpid(pid, &status, 0) != -1)
		if(WIFEXITED(status))
		{
			fprintf(stderr, "%s: %s%d\n", progname,
					"Terminated with error code ",
					WEXITSTATUS(status));
			return -1;
		}
		else if(WIFSIGNALED(status))
		{
			if(WTERMSIG(status) == SIGABRT)
				return 0;
			fprintf(stderr, "%s: %s%d\n", progname,
					"Terminated with signal ",
					WTERMSIG(status));
			return -1;
		}
	return -_error(progname, "waitpid", 1);
}

static int _ssp_child(char const * progname, unsigned int pattern)
{
	_ssp_child_sub(progname, pattern);
	_exit(2);
	return 2;
}

void _ssp_child_sub(char const * progname, unsigned int pattern)
{
	char buf[32];

	printf("%s: Testing SSP (%#08x)\n", progname, pattern);
	memset(buf, pattern, sizeof(buf) * 8);
}


/* error */
static int _error(char const * progname, char const * message, int ret)
{
	fprintf(stderr, "%s: %s: %s\n", progname, message, strerror(errno));
	return ret;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int ret = 0;

	ret += _ssp(argv[0], 0x41414141);
	ret += _ssp(argv[0], 0x00000000);
	return (ret == 0) ? 0 : 2;
}
