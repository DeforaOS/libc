/* $Id$ */
/* Copyright (c) 2016-2017 Pierre Pronchery <khorben@defora.org> */
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
/* FIXME:
 * - taken from NetBSD */



#ifndef LIBC_KERNEL_DARWIN_UTMPX_H
# define LIBC_KERNEL_DARWIN_UTMPX_H

# define _UTMPX_ID_SIZE		4
# define _UTMPX_LINE_SIZE	32
# define _UTMPX_USER_SIZE	32


/* types */
#ifndef timeval
# define timeval timeval
struct timeval
{
	time_t tv_sec;
	suseconds_t tv_usec;
};
#endif

struct utmpx
{
	char ut_user[_UTMPX_USER_SIZE];
	char ut_id[_UTMPX_ID_SIZE];
	char ut_line[_UTMPX_LINE_SIZE];
	pid_t ut_pid;
	short ut_type;
	struct timeval ut_tv;
	char _padding[272];
};

#endif /* !LIBC_KERNEL_DARWIN_UTMPX_H */
