/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_LINUX_SIGNAL_H
# define LIBC_KERNEL_LINUX_SIGNAL_H


/* types */
#ifndef pid_t
# define pid_t pid_t
typedef signed int pid_t;
#endif

typedef struct
{
	int si_signo;
	int si_errno;
	int si_code;
	int _padding0[28];
	int _padding1[5];
} siginfo_t;

typedef struct { unsigned long bits[16]; } sigset_t;

struct sigaction
{
	union
	{
		void (*sa_handler)(int);
		void (*sa_sigaction)(int, siginfo_t *, void *);
	} _sa_u;
	sigset_t sa_mask;
	int sa_flags;
	void * _padding;
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
# define SIGBUS		7
# define SIGFPE		8
# define SIGKILL	9
# define SIGUSR1	10
# define SIGSEGV	11
# define SIGUSR2	12
# define SIGPIPE	13
# define SIGALRM	14
# define SIGTERM	15
# define SIGCHLD	17
# define SIGCONT	18
# define SIGSTOP	19

# define SIG_DFL	((void (*)(int)) 0)
# define SIG_ERR	((void (*)(int)) -1)
# define SIG_HOLD	((void (*)(int)) 2)
# define SIG_IGN	((void (*)(int)) 1)

# define SIG_BLOCK	0
# define SIG_UNBLOCK	1
# define SIG_SETMASK	2

# define SA_RESTART	0
# define SA_NOCLDSTOP	1

#endif /* !LIBC_KERNEL_LINUX_SIGNAL_H */
