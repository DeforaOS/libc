/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#ifndef LIBC_KERNEL_FREEBSD_SIGNAL_H
# define LIBC_KERNEL_FREEBSD_SIGNAL_H


/* types */
typedef struct _siginfo_t siginfo_t;

typedef struct { unsigned int bits[4]; } sigset_t;

struct sigaction
{
	union
	{
		void (*sa_handler)(int);
		void (*sa_sigaction)(int, siginfo_t *, void *);
	} _sa_u;
	int sa_flags;
	sigset_t sa_mask;
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
# define SIGKILL	9
# define SIGSEGV	11
# define SIGPIPE	13
# define SIGTERM	15
# define SIGSTOP	17
# define SIGCONT	19
# define SIGCHLD	20
# define SIGUSR1	30
# define SIGUSR2	31

# define SIG_ERR	((void (*)(int)) -1)

# define SIG_BLOCK	1


/* functions */
int sigemptyset(sigset_t * set);

#endif /* !LIBC_KERNEL_FREEBSD_SIGNAL_H */
