/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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
