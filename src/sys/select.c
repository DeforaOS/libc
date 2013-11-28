/* $Id$ */
/* Copyright (c) 2007-2013 Pierre Pronchery <khorben@defora.org> */
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



#include "stddef.h"
#include "errno.h"
#include "../syscalls.h"
#include "sys/select.h"


/* pselect */
#ifndef SYS_pselect
# ifdef SYS_select
int pselect(int fdcnt, fd_set * rfds, fd_set * wfds, fd_set * efds,
		const struct timespec * timeout, const sigset_t * sigmask)
{
	struct timeval tv;
	struct timeval * tvp = NULL;

	if(timeout != NULL)
	{
		tv.tv_sec = timeout->tv_sec;
		tv.tv_usec = timeout->tv_nsec * 1000;
		tvp = &tv;
	}
	if(sigmask != NULL)
	{
		/* FIXME implement equivalent functionality */
		errno = ENOSYS;
		return -1;
	}
	return select(fdcnt, rfds, wfds, efds, tvp);
}
# else
#  warning Unsupported platform: pselect() is missing
int pselect(int fdcnt, fd_set * rfds, fd_set * wfds, fd_set * efds,
		const struct timespec * timeout, const sigset_t * sigmask)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif


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
