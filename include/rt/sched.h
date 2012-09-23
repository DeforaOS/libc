/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SCHED_H
# define LIBC_SCHED_H

# include <time.h>


/* types */
# ifndef pid_t
#  define pid_t pid_t
typedef signed int pid_t;
# endif

struct sched_param
{
	int sched_priority;
};


/* functions */
int sched_get_priority_max(int policy);
int sched_get_priority_min(int policy);
int sched_getparam(pid_t pid, struct sched_param * param);
int sched_getscheduler(pid_t pid);
int sched_rr_get_interval(pid_t pid, struct timespec * interval);
int sched_setparam(pid_t pid, const struct sched_param * param);
int sched_setscheduler(pid_t pid, int policy, const struct sched_param * param);
int sched_yield(void);

#endif /* !LIBC_SCHED_H */
