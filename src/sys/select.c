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



#include "errno.h"
#include "../syscalls.h"
#include "sys/select.h"


/* select */
#ifndef SYS_select
# warning Unsupported platform: select() is missing
int select(int fdcnt, fd_set * rfds, fd_set * wfds, fd_set * efds,
		struct timeval * timeout)
{
	errno = ENOSYS;
	return -1;
}
#endif
