/* $Id$ */
/* Copyright (c) 2007-2012 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_NETBSD_SYS_TYPES_H
# define LIBC_KERNEL_NETBSD_SYS_TYPES_H


/* types */
# ifndef blkcnt_t
#  define blkcnt_t blkcnt_t
typedef unsigned long long blkcnt_t;
# endif
# ifndef clock_t
#  define clock_t clock_t
typedef unsigned int clock_t;
# endif
# ifndef clockid_t
#  define clockid_t clockid_t
typedef int clockid_t;
# endif
# ifndef dev_t
#  define dev_t dev_t
typedef unsigned long long dev_t;
# endif
# ifndef fsblkcnt_t
#  define fsblkcnt_t fsblkcnt_t
typedef unsigned long long fsblkcnt_t;
# endif
# ifndef fsfilcnt_t
#  define fsfilcnt_t fsfilcnt_t
typedef unsigned long long fsfilcnt_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif
# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef int suseconds_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef long long time_t;
# endif
# ifndef useconds_t
#  define useconds_t useconds_t
typedef unsigned int useconds_t;
# endif

#endif /* !LIBC_KERNEL_NETBSD_SYS_TYPES_H */
