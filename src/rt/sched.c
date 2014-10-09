/* $Id$ */
/* Copyright (c) 2012-2014 Pierre Pronchery <khorben@defora.org> */
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



#include "unistd.h"
#include "syscalls.h"
#include "sched.h"
#include "errno.h"


/* functions */
/* sched_get_priority_max */
int sched_get_priority_max(int policy)
{
#ifdef _SC_SCHED_PRI_MAX
	return sysconf(_SC_SCHED_PRI_MAX);
#else
	errno = ENOSYS;
	return -1;
#endif
}


/* sched_get_priority_min */
int sched_get_priority_min(int policy)
{
#ifdef _SC_SCHED_PRI_MIN
	return sysconf(_SC_SCHED_PRI_MIN);
#else
	errno = ENOSYS;
	return -1;
#endif
}


/* sched_getparam */
#ifndef SYS_sched_getparam
int sched_getparam(pid_t pid, struct sched_param * param)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* sched_getscheduler */
#ifndef SYS_sched_getscheduler
int sched_getscheduler(pid_t pid)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* sched_rr_get_interval */
int sched_rr_get_interval(pid_t pid, struct timespec * interval)
{
#ifdef _SC_SCHED_RT_TS
	long l;

	if((l = sysconf(_SC_SCHED_RT_TS)) < 0)
		return -1;
	interval->tv_nsec = l * 1000;
	interval->tv_sec = interval->tv_nsec / 1000000000;
	interval->tv_nsec -= (interval->tv_sec * 1000000000);
	return 0;
#else
	errno = ENOSYS;
	return -1;
#endif
}


/* sched_setparam */
#ifndef SYS_sched_setparam
int sched_setparam(pid_t pid, const struct sched_param * param)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* sched_setscheduler */
#ifndef SYS_sched_setscheduler
int sched_setscheduler(pid_t pid, int policy, const struct sched_param * param)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* sched_yield */
#ifndef SYS_sched_yield
int sched_yield(void)
{
	errno = ENOSYS;
	return -1;
}
#endif
