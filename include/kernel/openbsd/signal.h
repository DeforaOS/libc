/* $Id$ */
/* Copyright (c) 2007-2016 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_OPENBSD_SIGNAL_H
# define LIBC_KERNEL_OPENBSD_SIGNAL_H


/* types */
typedef struct
{
	int si_signo;
	int si_code;
	int si_error;
	/* FIXME to be completed */
} siginfo_t;

typedef unsigned int sigset_t;

struct sigaction
{
	union
	{
		void    (*sa_handler)(int);
		void    (*sa_sigaction)(int, siginfo_t *, void *);
	} _sa_u;
	sigset_t sa_mask;
	int sa_flags;
};
# define sa_handler _sa_u.sa_handler
# define sa_sigaction _sa_u.sa_sigaction

/* constants */
# define SIGHUP		1
# define SIGINT		2
# define SIGQUIT	3
# define SIGILL		4
# define SIGTRAP	5
# define SIGABRT	6
# define SIGIOT		6
# define SIGFPE		8
# define SIGKILL	9
# define SIGBUS		10
# define SIGSEGV	11
# define SIGPIPE	13
# define SIGALRM	14
# define SIGTERM	15
# define SIGSTOP	17
# define SIGTSTP	18
# define SIGCONT	19
# define SIGCHLD	20
# define SIGUSR1	30
# define SIGUSR2	31

# define SIG_DFL	((void (*)(int)) 0)
# define SIG_ERR	((void (*)(int)) -1)
# define SIG_IGN	((void (*)(int)) 1)

# define SA_RESTART	0x2

#endif /* !LIBC_KERNEL_OPENBSD_SIGNAL_H */
