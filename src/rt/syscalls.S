/* $Id$ */
/* Copyright (c) 2014 Pierre Pronchery <khorben@defora.org> */
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



#include "syscalls.h"


.text


/* Unknown */
#warning Unsupported platform
#ifndef SYSCALL
# define SYSCALL(name)
#endif


/* sched.h */
#ifdef SYS_sched_getparam
SYSCALL(sched_getparam)
#endif
#ifdef SYS_sched_getscheduler
SYSCALL(sched_getscheduler)
#endif
#ifdef SYS_sched_setparam
SYSCALL(sched_setparam)
#endif
#ifdef SYS_sched_setscheduler
SYSCALL(sched_setscheduler)
#endif
#ifdef SYS_sched_yield
SYSCALL(sched_yield)
#endif
