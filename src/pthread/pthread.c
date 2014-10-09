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



#include "sys/types.h" /* FIXME should not be needed? */
#include "errno.h"
#include "pthread.h"


/* pthread_attr_destroy */
int pthread_attr_destroy(pthread_attr_t * attr)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_attr_getdetachstate */
int pthread_attr_getdetachstate(const pthread_attr_t * attr, int * state)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_attr_getstacksize */
int pthread_attr_getstacksize(const pthread_attr_t * attr, size_t * stacksize)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_attr_init */
int pthread_attr_init(pthread_attr_t * attr)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_attr_setdetachstate */
int pthread_attr_setdetachstate(pthread_attr_t * attr, int state)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_attr_setstacksize */
int pthread_attr_setstacksize(pthread_attr_t * attr, size_t stacksize)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_cancel */
int pthread_cancel(pthread_t thread)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_cond_broadcast */
int pthread_cond_broadcast(pthread_cond_t * cond)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_cond_destroy */
int pthread_cond_destroy(pthread_cond_t * cond)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_cond_init */
int pthread_cond_init(pthread_cond_t * cond, const pthread_condattr_t * attr)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_cond_signal */
int pthread_cond_signal(pthread_cond_t * cond)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_cond_timedwait */
int pthread_cond_timedwait(pthread_cond_t * cond,
		pthread_mutex_t * mutex, const struct timespec * ts)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_cond_wait */
int pthread_cond_wait(pthread_cond_t * cond, pthread_mutex_t * mutex)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_create */
int pthread_create(pthread_t * thread, const pthread_attr_t * attr,
		void *(*start)(void *), void * arg)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_exit */
void pthread_exit(void * value)
{
	/* FIXME implement */
}


/* pthread_join */
int pthread_join(pthread_t thread, void ** value)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_mutex_destroy */
int pthread_mutex_destroy(pthread_mutex_t * mutex)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_mutex_init */
int pthread_mutex_init(pthread_mutex_t * mutex,
		const pthread_mutexattr_t * attr)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_mutex_lock */
int pthread_mutex_lock(pthread_mutex_t * mutex)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_mutex_trylock */
int pthread_mutex_trylock(pthread_mutex_t * mutex)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_mutex_unlock */
int pthread_mutex_unlock(pthread_mutex_t * mutex)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* pthread_self */
pthread_t pthread_self(void)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}
