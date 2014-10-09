/* $Id$ */
/* Copyright (c) 2008-2013 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_PTHREAD_H
# define LIBC_PTHREAD_H

# include <sched.h>


/* types */
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
	/* FIXME really implement */
	unsigned int data;
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


/* constants */
enum { PTHREAD_CREATE_JOINABLE, PTHREAD_CREATE_DETACHED };

# define PTHREAD_MUTEX_INITIALIZER	{ 0 }


/* functions */
int pthread_atfork(void (*)(void), void (*)(void), void(*)(void));
int pthread_attr_destroy(pthread_attr_t *);
int pthread_attr_getdetachstate(const pthread_attr_t *, int *);
int pthread_attr_getstacksize(const pthread_attr_t *, size_t *);
int pthread_attr_init(pthread_attr_t *);
int pthread_attr_setdetachstate(pthread_attr_t *, int);
int pthread_attr_setstacksize(pthread_attr_t *, size_t);
int pthread_barrier_destroy(pthread_barrier_t *);
int pthread_barrier_init(pthread_barrier_t *, const pthread_barrierattr_t *,
		unsigned);
int pthread_barrier_wait(pthread_barrier_t *);
int pthread_barrierattr_destroy(pthread_barrierattr_t *);
int pthread_cancel(pthread_t);
void pthread_cleanup_push(void (*)(void *), void *);
void pthread_cleanup_pop(int);
int pthread_cond_broadcast(pthread_cond_t *);
int pthread_cond_destroy(pthread_cond_t *);
int pthread_cond_init(pthread_cond_t *, const pthread_condattr_t *);
int pthread_cond_signal(pthread_cond_t *);
int pthread_cond_timedwait(pthread_cond_t *,
		pthread_mutex_t *, const struct timespec *);
int pthread_cond_wait(pthread_cond_t *, pthread_mutex_t *);
int pthread_condattr_destroy(pthread_condattr_t *);
int pthread_create(pthread_t *, const pthread_attr_t *,
		void *(*)(void *), void *);
int pthread_detach(pthread_t);
int pthread_equal(pthread_t, pthread_t);
void pthread_exit(void *);
void * pthread_getspecific(pthread_key_t);
int pthread_join(pthread_t, void **);
int pthread_key_create(pthread_key_t *, void (*)(void *));
int pthread_key_delete(pthread_key_t);
int pthread_mutex_destroy(pthread_mutex_t *);
int pthread_mutex_init(pthread_mutex_t *, const pthread_mutexattr_t *);
int pthread_mutex_lock(pthread_mutex_t *);
int pthread_mutex_trylock(pthread_mutex_t *);
int pthread_mutex_unlock(pthread_mutex_t *);
int pthread_mutexattr_destroy(pthread_mutexattr_t *);
pthread_t pthread_self(void);
int pthread_setcancelstate(int, int *);
int pthread_setcanceltype(int, int *);
int pthread_spin_destroy(pthread_spinlock_t *);
int pthread_spin_init(pthread_spinlock_t *, int);
int pthread_spin_lock(pthread_spinlock_t *);
int pthread_spin_trylock(pthread_spinlock_t *);
int pthread_spin_unlock(pthread_spinlock_t *);
void pthread_testcancel(void);

#endif /* !LIBC_PTHREAD_H */
