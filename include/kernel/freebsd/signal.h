/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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
# define SIGINT		2
# define SIGABRT	6
# define SIGTERM	15

# define SIG_ERR	((void (*)(int)) -1)

# define SIG_BLOCK	1


/* functions */
int sigemptyset(sigset_t * set);

#endif /* !LIBC_KERNEL_FREEBSD_SIGNAL_H */
