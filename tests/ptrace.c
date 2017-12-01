/* $Id$ */
/* Copyright (c) 2012-2015 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


/* prototypes */
static int _ptrace(char const * progname);

static int _error(char const * progname, char const * message, int ret);


/* functions */
/* ptrace */
static int _ptrace_child(char const * progname);

static int _ptrace(char const * progname)
{
	int ret = 0;
	pid_t pid;
	pid_t p;
	int status;

	if((pid = fork()) < 0)
		return -_error(progname, "fork", 1);
	if(pid == 0)
		return _ptrace_child(progname);
	for(;;)
		if((p = waitpid(pid, &status, 0)) == pid)
		{
			if(WIFEXITED(status))
			{
				ret = WEXITSTATUS(status);
				break;
			}
			else if(WIFSIGNALED(status))
			{
				ret = 1;
				break;
			}
			else if(WIFSTOPPED(status)
					&& ptrace(PT_CONTINUE, pid, (void *)1,
						0) == 0)
				break;
		}
		else if(p == -1)
		{
			ret = -_error(progname, "waitpid", 1);
			if(errno == ECHILD)
				break;
		}
	return ret;
}

static int _ptrace_child(char const * progname)
{
	int ret = 0;

	errno = 0;
	if(ptrace(PT_TRACE_ME, 0, NULL, 0) != 0 && errno != 0)
		ret = _error(progname, "PT_TRACE_ME", 1) + 1;
	_exit(ret);
	return -_error(progname, "exit", 1);
}


/* error */
static int _error(char const * progname, char const * message, int ret)
{
	fprintf(stderr, "%s: %s: %s\n", progname, message, strerror(errno));
	return ret;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret |= _ptrace(argv[0]);
	return (ret == 0) ? 0 : 2;
}
