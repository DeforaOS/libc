/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#include "../syscalls.h"
#include "sys/wait.h"


/* wait */
#ifndef SYS_wait
pid_t wait(int * status)
{
	return waitpid(-1, status, 0);
}
#endif /* !SYS_wait */


/* waitpid */
#if !defined(SYS_waitpid)
# if defined(SYS_wait4)
#  include "stdlib.h"
pid_t wait4(pid_t pid, int * status, int options, void * rusage);

pid_t waitpid(pid_t pid, int * status, int options)
{
	return wait4(pid, status, options, NULL);
}
# else
#  warning Unsupported platform: waitpid() is missing
#  include "errno.h"
pid_t waitpid(pid_t pid, int * status, int options)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif
