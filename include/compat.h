/* $Id$ */
/* Copyright (c) 2016-2019 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_COMPAT_H
# define LIBC_COMPAT_H


# if defined(__FreeBSD__)
#  include "kernel/freebsd/compat.h"
# elif defined(__linux__)
#  include "kernel/linux/compat.h"
# elif defined(__OpenBSD__)
#  include "kernel/openbsd/compat.h"
# elif defined(__sun__)
#  include "kernel/solaris/compat.h"
# elif defined(__Whitix__)
#  include "kernel/whitix/compat.h"
# endif


/* types */
# ifndef __blkcnt_t
#  define __blkcnt_t unsigned long long
# endif
# ifndef __blksize_t
#  define __blksize_t unsigned int
# endif
# ifndef __clock_t
#  define __clock_t unsigned int
# endif
# ifndef __clockid_t
#  define __clockid_t int
# endif
# ifndef __dev_t
#  define __dev_t unsigned long long
# endif
# ifndef __fsblkcnt_t
#  define __fsblkcnt_t unsigned long long
# endif
# ifndef __fsfilcnt_t
#  define __fsfilcnt_t unsigned long long
# endif
# ifndef __iconv_t
#  define __iconv_t unsigned int
# endif
# ifndef __id_t
#  define __id_t unsigned int
# endif
# ifndef __ino_t
#  define __ino_t unsigned long long
# endif
# ifndef __intptr_t
#  define __intptr_t long
# endif
# ifndef __key_t
#  define __key_t long
# endif
# ifndef __mode_t
#  define __mode_t unsigned int
# endif
# ifndef __nlink_t
#  define __nlink_t unsigned int
# endif
# ifndef __off_t
#  define __off_t long long
# endif
# ifndef __paddr_t
#  define __paddr_t unsigned long
# endif
# ifndef __pid_t
#  define __pid_t int
# endif
# ifndef __ptrdiff_t
#  define __ptrdiff_t long
# endif
# ifndef __rlim_t
#  define __rlim_t unsigned long long
# endif
# ifndef __size_t
#  define __size_t unsigned long
# endif
# ifndef __ssize_t
#  define __ssize_t long
# endif
# ifndef __suseconds_t
#  define __suseconds_t int
# endif
# ifndef __time_t
#  define __time_t long long
# endif
# ifndef __uintptr_t
#  define __uintptr_t unsigned long
# endif
# ifndef __useconds_t
#  define __useconds_t unsigned int
# endif
# ifndef __va_list
#  if defined(__GNUC__) && __GNUC__ >= 3
#   define __va_list __builtin_va_list
#  else
#   warning Unsupported architecture: va_list is not supported
#   define __va_list char *
#  endif
# endif
# ifndef __vaddr_t
#  define __vaddr_t unsigned long
# endif
# ifndef __wchar_t
#  define __wchar_t char
# endif
# ifndef __wint_t
#  define __wint_t int
# endif

# ifndef __gid_t
#  define __gid_t __id_t
# endif
# ifndef __uid_t
#  define __uid_t __id_t
# endif

#endif /* !LIBC_COMPAT_H */
