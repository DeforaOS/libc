/* $Id$ */
/* Copyright (c) 2007-2015 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_LINUX_ERRNO_H
# define LIBC_KERNEL_LINUX_ERRNO_H


/* constants */
# define EPERM		1
# define ENOENT		2
# define ESRCH		3
# define EINTR		4
# define EIO		5
# define ENXIO		6
# define E2BIG		7
# define ENOEXEC	8
# define EBADF		9
# define ECHILD		10
# define EAGAIN		11
# define ENOMEM		12
# define EACCES		13
# define EFAULT		14
# define EBUSY		16
# define EEXIST		17
# define EXDEV		18
# define ENODEV		19
# define ENOTDIR	20
# define EISDIR		21
# define EINVAL		22
# define ENOTTY		25
# define ENOSPC		28
# define ESPIPE		29
# define EROFS		30
# define EPIPE		32
# define EDOM		33
# define ERANGE		34
# define ENOSYS		38
# define ENOTEMPTY	39
# define ELOOP		40
# define EPROTO		71
# define ENOTSUP	95
# define EOPNOTSUPP	95
# define EADDRINUSE	98
# define EADDRNOTAVAIL	99
# define ENOBUFS	105
# define ETIMEDOUT	110
# define ECONNREFUSED	111
# define EINPROGRESS	115

#endif /* !LIBC_KERNEL_LINUX_ERRNO_H */
