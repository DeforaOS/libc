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



#ifndef LIBC_KERNEL_NETBSD_SYS_SELECT_H
# define LIBC_KERNEL_NETBSD_SYS_SELECT_H

/* XXX for memset() */
# include <string.h>


/* types */
# ifndef fd_set
#  define fd_set fd_set
typedef struct _fd_set
{
	int fds_bits[8];
} fd_set;
# endif

# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef int suseconds_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef long long time_t;
# endif
# ifndef timeval
#  define timeval timeval
struct timeval
{
	time_t tv_sec;
	suseconds_t tv_usec;
};
# endif


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
# define FD_SETSIZE	256

#endif /* !LIBC_KERNEL_NETBSD_SYS_SELECT_H */
