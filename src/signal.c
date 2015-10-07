/* $Id$ */
/* Copyright (c) 2005-2015 Pierre Pronchery <khorben@defora.org> */
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



#include "unistd.h"
#include "string.h"
#include "errno.h"
#include "syscalls.h"
#include "signal.h"


/* functions */
/* kill */
#ifndef SYS_kill
# warning Unsupported platform: kill() is missing
int kill(pid_t pid, int sig)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* raise */
int raise(int sig)
{
	return kill(getpid(), sig);
}


/* sigaction */
#ifndef SYS_sigaction
# warning Unsupported platform: sigaction() is missing
int sigaction(int sig, const struct sigaction * act, struct sigaction * oact)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* sigaddset */
int sigaddset(sigset_t * set, int sig)
{
	if(sig < 0 || (size_t)sig > (sizeof(set->bits) / sizeof(*set->bits)))
	{
		errno = EINVAL;
		return -1;
	}
	set->bits[(sig - 1) >> 5] |= (sig % 32);
	return 0;
}


/* sigdelset */
int sigdelset(sigset_t * set, int sig)
{
	if(sig < 0 || (size_t)sig > (sizeof(set->bits) / sizeof(*set->bits)))
	{
		errno = EINVAL;
		return -1;
	}
	set->bits[(sig - 1) >> 5] &= ~(sig % 32);
	return 0;
}


/* sigemptyset */
#undef sigemptyset
int sigemptyset(sigset_t * set)
{
	memset(set, 0, sizeof(*set));
	return 0;
}


/* sigfillset */
#undef sigfillset
int sigfillset(sigset_t * set)
{
	memset(set, ~0, sizeof(*set));
	return 0;
}


/* sigismember */
int sigismember(const sigset_t * set, int sig)
{
	if(sig < 0 || (size_t)sig > (sizeof(set->bits) / sizeof(*set->bits)))
		return 0;
	return (set->bits[(sig - 1) >> 5] & (sig % 32));
}


/* sigprocmask */
#ifndef SYS_sigprocmask
# warning Unsupported platform: sigprocmask() is missing
int sigprocmask(int how, const sigset_t * set, sigset_t * oset)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* signal */
#ifndef SYS_signal
static sigset_t _sigintr;

void (*signal(int sig, void (*func)(int)))
{
	struct sigaction sa;
	struct sigaction osa;

	sa.sa_sigaction = NULL;
	sa.sa_handler = func;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0; /* XXX ? */
	if(sigismember(&_sigintr, sig) == 0)
		sa.sa_flags |= SA_RESTART;
	if(sigaction(sig, &sa, &osa) != 0)
		return SIG_ERR;
	return osa.sa_handler;
}
#endif /* !SYS_signal */
