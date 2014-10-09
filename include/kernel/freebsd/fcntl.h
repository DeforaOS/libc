/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_FREEBSD_FCNTL_H
# define LIBC_KERNEL_FREEBSD_FCNTL_H


/* types */
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef signed int pid_t;
# endif

struct flock
{
	off_t l_start;
	off_t l_len;
	pid_t l_pid;
	short l_type;
	short l_whence;
	int _padding;
};


/* constants */
# define F_DUPFD	0
# define F_GETFD	1
# define F_SETFD	2
# define F_GETFL	3
# define F_SETFL	4
# define F_GETOWN	5
# define F_SETOWN	6
# define F_GETLK	7
# define F_SETLK	8
# define F_SETLKW	9

# define FD_CLOEXEC	1

# define F_RDLCK	1
# define F_UNLCK	2
# define F_WRLCK	3

# define O_CREAT	0x0200
# define O_EXCL		0x0800
# define O_NOCTTY	0x8000
# define O_TRUNC	0x0400

# define O_NONBLOCK	0x00004
# define O_APPEND	0x00008
# define O_SYNC		0x00080

# define O_RDONLY	0
# define O_WRONLY	1
# define O_RDWR		2

# define O_ACCMODE	(O_WRONLY | O_RDWR)

# define LOCK_SH	0x1
# define LOCK_EX	0x2
# define LOCK_NB	0x4
# define LOCK_UN	0x8

#endif /* !LIBC_KERNEL_FREEBSD_FCNTL_H */
