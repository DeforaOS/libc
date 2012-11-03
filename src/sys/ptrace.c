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



#include "sys/types.h"
#include "errno.h"
#include "../syscalls.h"
#include "sys/ptrace.h"


/* functions */
/* ptrace */
#ifndef SYS_ptrace
# warning Unsupported platform: ptrace() is missing
int ptrace(int request, pid_t pid, void * address, int data)
{
	errno = ENOSYS;
	return -1;
}
#endif
