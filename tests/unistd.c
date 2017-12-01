/* $Id$ */
/* Copyright (c) 2013-2016 Pierre Pronchery <khorben@defora.org> */
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <libgen.h>
#include <unistd.h>
#include <errno.h>


/* chroot */
static int _chroot(char const * progname)
{
	char * p;
	char * dir;
	int res;

	printf("%s: Testing chroot()\n", progname);
	if((p = strdup(progname)) == NULL)
		return -1;
	dir = dirname(p);
	res = chroot(dir);
	free(p);
	if(res != 0)
		switch(errno)
		{
			case ENOSYS:
			case EPERM:
				/* we can ignore these errors */
				break;
			default:
				return -1;
		}
	return 0;
}


/* fork */
static int _fork(char const * progname)
{
	pid_t pid;
	int res = 42;
	pid_t p;
	int status;

	printf("%s: Testing fork()\n", progname);
	if((pid = fork()) == -1)
		return -1;
	if(pid == 0)
		/* child process */
		_exit(res);
	/* parent process */
	for(;;)
	{
		if((p = waitpid(pid, &status, 0)) == -1)
			break;
		if(p != pid)
			continue;
		if(WIFEXITED(status) && WEXITSTATUS(status) == res)
			return 0;
	}
	return -1;
}


/* sleep */
static int _sleep(char const * progname, unsigned int t)
{
	time_t before;
	time_t after;
	int res;

	printf("%s: Testing sleep()\n", progname);
	before = time(NULL);
	res = sleep(t);
	after = time(NULL);
	if(res == 0)
		return (after - before == t) ? 0 : -1;
	/* XXX ignore other cases (signal deliveries...) */
	return 0;
}


/* main */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret += _chroot(argv[0]);
	ret += _fork(argv[0]);
	ret += _sleep(argv[0], 0);
	ret += _sleep(argv[0], 1);
	return (ret == 0) ? 0 : 2;
}
