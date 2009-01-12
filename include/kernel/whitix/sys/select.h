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



#ifndef LIBC_KERNEL_WHITIX_SYS_SELECT_H
# define LIBC_KERNEL_WHITIX_SYS_SELECT_H


/* FIXME nothing checked */
/* types */
# ifndef fd_set
#  define fd_set fd_set
typedef struct _fd_set
{
	long fds_bits[8];
} fd_set;
# endif
# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef int suseconds_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef unsigned int time_t;
# endif
#ifndef timeval
# define timeval timeval
struct timeval
{
	time_t tv_sec;
	suseconds_t tv_usec;
};
#endif


/* macros */
# define FD_CLR(fd, fdset)	\
	((fdset)->fds_bits[(fd) / 32] &= ~(1 << ((fd) % 8)))
# define FD_ISSET(fd, fdset)	\
	((fdset)->fds_bits[(fd) / 32] & (1 << ((fd) % 8)))
# define FD_SET(fd, fdset)	\
	((fdset)->fds_bits[(fd) / 32] |= (1 << ((fd) % 8)))
# define FD_ZERO(fdset)		\
	memset(fdset, 0, sizeof(fd_set))


/* constants */
# define FD_SETSIZE	1024

#endif /* !LIBC_KERNEL_WHITIX_SYS_SELECT_H */
