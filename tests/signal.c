/* $Id$ */
/* Copyright (c) 2012-2020 Pierre Pronchery <khorben@defora.org> */
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
#include <signal.h>
#include <stdio.h>


/* signal */
/* private */
/* variables */
static int _ret;


/* prototypes */
static int _sigismember(char const * progname, int signal);

static void _on_sigusr1(int signal);
static void _on_sigusr2(int signal);

static int _error(char const * progname, char const * message, int ret);


/* functions */
/* sigismember */
static int _sigismember(char const * progname, int signal)
{
	sigset_t set;

	printf("%s: Testing sigismember(%d)\n", progname, signal);
	if(sigemptyset(&set) != 0 || sigismember(&set, signal))
		return 1;
	if(sigaddset(&set, signal) != 0 || sigismember(&set, signal) == 0)
		return 2;
	if(sigdelset(&set, signal) != 0 || sigismember(&set, signal))
		return 4;
	if(sigfillset(&set) != 0 || sigismember(&set, signal) == 0)
		return 8;
	return 0;
}


/* on_sigusr1 */
static void _on_sigusr1(int signal)
{
	(void) signal;

	if(_ret == 3)
		_ret = 0;
}


/* on_sigusr2 */
static void _on_sigusr2(int signal)
{
	(void) signal;

	if(_ret == 2)
		_ret = 3;
}


/* error */
static int _error(char const * progname, char const * message, int ret)
{
	fprintf(stderr, "%s: ", progname);
	perror(message);
	return ret;
}


/* public */
/* functions */
int main(int argc, char * argv[])
{
	int ret = 0;
	(void) argc;

	ret = (_sigismember(argv[0], SIGHUP) << 2);
	_ret = 2;
	printf("%s: %s", argv[0], "Testing signal()\n");
	if(signal(SIGUSR1, _on_sigusr1) == SIG_ERR)
		_error(argv[0], "signal", 2);
	if(signal(SIGUSR2, _on_sigusr2) == SIG_ERR)
		_error(argv[0], "signal", 2);
	if(signal(SIGKILL, SIG_IGN) != SIG_ERR)
		fprintf(stderr, "%s: %s: %s\n", argv[0], "signal",
				"Should not allow ignoring SIGKILL");
	if(signal(SIGTERM, SIG_IGN) == SIG_ERR)
		_error(argv[0], "signal", 2);
	printf("%s: %s", argv[0], "Testing kill()\n");
	if(raise(SIGUSR2) != 0)
		_error(argv[0], "kill", 2);
	if(raise(SIGUSR1) != 0)
		_error(argv[0], "kill", 2);
	if(raise(SIGTERM) != 0)
		_error(argv[0], "kill", 2);
	return (ret | _ret);
}
