/* $Id$ */
/* Copyright (c) 2007-2013 Pierre Pronchery <khorben@defora.org> */
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
