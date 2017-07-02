/* $Id$ */
/* Copyright (c) 2005-2017 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SYS_TYPES_H
# define LIBC_SYS_TYPES_H

# include "../compat.h"


/* types */
# ifndef blksize_t
#  define blksize_t blksize_t
typedef __blksize_t blksize_t;
# endif
# ifndef clock_t
#  define clock_t clock_t
typedef __clock_t clock_t;
# endif
# ifndef clockid_t
#  define clockid_t clockid_t
typedef __clockid_t clockid_t;
# endif
# ifndef gid_t
#  define gid_t gid_t
typedef __gid_t gid_t;
# endif
# ifndef id_t
#  define id_t id_t
typedef __id_t id_t;
# endif
# ifndef key_t
#  define key_t key_t
typedef __key_t key_t;
# endif
# ifndef mode_t
#  define mode_t mode_t
typedef __mode_t mode_t;
# endif
# ifndef nlink_t
#  define nlink_t nlink_t
typedef __nlink_t nlink_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef __off_t off_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef __pid_t pid_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef __size_t size_t;
# endif
# ifndef ssize_t
#  define ssize_t ssize_t
typedef __ssize_t ssize_t;
# endif
# ifndef suseconds_t
#  define suseconds_t suseconds_t
typedef __suseconds_t suseconds_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef __uid_t uid_t;
# endif
# ifndef useconds_t
#  define useconds_t useconds_t
typedef __useconds_t useconds_t;
# endif

/* pthread */
# ifndef pthread_attr_t
#  define pthread_attr_t pthread_attr_t
typedef struct
{
	/* FIXME implement */
} pthread_attr_t;
# endif
# ifndef pthread_barrier_t
#  define pthread_barrier_t pthread_barrier_t
typedef struct
{
	/* FIXME implement */
} pthread_barrier_t;
# endif
# ifndef pthread_barrierattr_t
#  define pthread_barrierattr_t pthread_barrierattr_t
typedef struct
{
	/* FIXME implement */
} pthread_barrierattr_t;
# endif
# ifndef pthread_cond_t
#  define pthread_cond_t pthread_cond_t
typedef struct
{
	/* FIXME implement */
} pthread_cond_t;
# endif
# ifndef pthread_condattr_t
#  define pthread_condattr_t pthread_condattr_t
typedef struct
{
	/* FIXME implement */
} pthread_condattr_t;
# endif
# ifndef pthread_key_t
#  define pthread_key_t pthread_key_t
typedef unsigned int pthread_key_t;
# endif
# ifndef pthread_mutex_t
#  define pthread_mutex_t pthread_mutex_t
typedef struct
{
	/* FIXME implement */
} pthread_mutex_t;
# endif
# ifndef pthread_mutexattr_t
#  define pthread_mutexattr_t pthread_mutexattr_t
typedef struct
{
	/* FIXME implement */
} pthread_mutexattr_t;
# endif
# ifndef pthread_once_t
#  define pthread_once_t pthread_once_t
typedef int pthread_once_t;
# endif
# ifndef pthread_rwlock_t
#  define pthread_rwlock_t pthread_rwlock_t
typedef struct
{
	/* FIXME implement */
} pthread_rwlock_t;
# endif
# ifndef pthread_rwlockattr_t
#  define pthread_rwlockattr_t pthread_rwlockattr_t
typedef struct
{
	/* FIXME implement */
} pthread_rwlockattr_t;
# endif
# ifndef pthread_spinlock_t
#  define pthread_spinlock_t pthread_spinlock_t
typedef volatile int pthread_spinlock_t;
# endif
# ifndef pthread_t
#  define pthread_t pthread_t
typedef unsigned long pthread_t;
# endif

#endif /* !LIBC_SYS_TYPES_H */
