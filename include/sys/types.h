/* $Id$ */
/* Copyright (c) 2005-2012 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#ifndef LIBC_SYS_TYPES_H
# define LIBC_SYS_TYPES_H

# include "compat/sys/types.h"


/* types */
# ifndef blksize_t
#  define blksize_t blksize_t
typedef unsigned int blksize_t;
# endif
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif
# ifndef key_t
#  define key_t key_t
typedef long key_t;
# endif
# ifndef mode_t
#  define mode_t mode_t
typedef unsigned int mode_t;
# endif
# ifndef nlink_t
#  define nlink_t nlink_t
typedef unsigned int nlink_t;
# endif
# ifndef pid_t
#  define pid_t pid_t
typedef signed int pid_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
# endif
# ifndef ssize_t
#  define ssize_t ssize_t
typedef signed long ssize_t;
# endif

# ifndef gid_t
#  define gid_t gid_t
typedef id_t gid_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef id_t uid_t;
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
