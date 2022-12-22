/* $Id$ */
/* Copyright (c) 2007-2022 Pierre Pronchery <khorben@defora.org> */
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


/* constants */
# ifndef FD_SETSIZE
#  define FD_SETSIZE	256
# endif


/* types */
# ifndef fd_set
#  define fd_set fd_set
typedef struct __fd_set
{
	unsigned int fds_bits[(((FD_SETSIZE)
				+ ((sizeof(unsigned int) << 3) - 1))
			/ (sizeof(unsigned int) << 3))];
} fd_set;
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
	((fdset)->fds_bits[(fd) / (sizeof((fdset)->fds_bits[0]) << 3)]	\
	 &= ~(1 << ((fd) & 0x7)))
# define FD_ISSET(fd, fdset)	\
	((fdset)->fds_bits[(fd) / (sizeof((fdset)->fds_bits[0]) << 3)]	\
	 & (1 << ((fd) & 0x7)))
# define FD_SET(fd, fdset)	\
	((fdset)->fds_bits[(fd) / (sizeof((fdset)->fds_bits[0]) << 3)]	\
	 |= (1 << ((fd) & 0x7)))
# define FD_ZERO(fdset)		\
	do								\
	{								\
		size_t n = 0;						\
		fd_set * p = (fdset);					\
									\
		while(n < (sizeof(p->fds_bits)				\
					/ sizeof(p->fds_bits[0])))	\
			p->fds_bits[n++] = 0;				\
	}								\
	while(0)

#endif /* !LIBC_KERNEL_NETBSD_SYS_SELECT_H */
