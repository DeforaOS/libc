/* $Id$ */
/* Copyright (c) 2012-2014 Pierre Pronchery <khorben@defora.org> */
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
