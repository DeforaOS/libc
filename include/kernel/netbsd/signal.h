/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



#ifndef LIBC_KERNEL_NETBSD_SIGNAL_H
# define LIBC_KERNEL_NETBSD_SIGNAL_H


/* types */
#ifndef pid_t
# define pid_t pid_t
typedef signed int pid_t;
#endif

typedef union /* FIXME to be completed */
{
	char _padding0[128];
	int si_signo;
	int si_code;
	int si_errno;
	int _padding1;
	int _padding2[5];
} siginfo_t;

typedef struct { unsigned int bits[4]; } sigset_t;

struct sigaction
{
	union
	{
		void (*sa_handler)(int);
		void (*sa_sigaction)(int, siginfo_t *, void *);
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
# define SIGCONT	19
# define SIGCHLD	20
# define SIGUSR1	30
# define SIGUSR2	31

# define SIG_ERR	((void (*)(int)) -1)


/* macros */
# define sigemptyset(s) ((s)->bits[0] = 0, (s)->bits[1] = 0, (s)->bits[2] = 0, \
		(s)->bits[3] = 0)

#endif /* !LIBC_KERNEL_NETBSD_SIGNAL_H */
