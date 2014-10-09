/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#include "../syscalls.h"
#include "sys/time.h"


/* functions */
/* getitimer */
#ifndef SYS_getitimer
# warning Unsupported platform: getitimer() is missing
# include "errno.h"
int getitimer(int which, struct itimerval * value)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* gettimeofday */
#ifndef SYS_gettimeofday
# warning Unsupported platform: gettimeofday() is missing
# include "errno.h"
int gettimeofday(struct timeval * tv, void * null)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* setitimer */
#ifndef SYS_setitimer
# warning Unsupported platform: setitimer() is missing
# include "errno.h"
int setitimer(int which, const struct itimerval * value,
		struct itimerval * ovalue)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* utimes */
#ifndef SYS_utimes
# warning Unsupported platform: utimes() is missing
#endif
