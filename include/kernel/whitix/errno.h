/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_WHITIX_ERRNO_H
# define LIBC_KERNEL_WHITIX_ERRNO_H


/* constants */
# define EPERM		1
# define ENOENT		2
# define EIO		3
# define EBADF		4
# define ENOMEM		5
# define EACCES		6
# define EBUSY		7
# define EFAULT		8
# define EEXIST		9
# define EMFILE		10
# define ENOSPC		11
# define EROFS		12
# define ENOSYS		13
# define ENOTDIR	15
# define EISDIR		17
# define EINVAL		18
# define EINTR		19
# define E2BIG		20
# define EAGAIN		22
# define ECHILD		23
# define ENOEXEC	24
# define EPIPE		32
# define ENOTTY		37
# define ENOBUFS	45
# define EXDEV		52
# define ERANGE		56
# define ENODEV		59

#endif /* !LIBC_KERNEL_WHITIX_ERRNO_H */
