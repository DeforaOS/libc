/* $Id$ */
/* Copyright (c) 2004-2015 Pierre Pronchery <khorben@defora.org> */
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



#include "errno.h"
#include "syscalls.h"
#include "fcntl.h"


/* functions */
/* creat */
#ifndef SYS_creat
# ifdef SYS_open
int creat(const char * filename, mode_t mode)
{
	return open(filename, O_CREAT | O_TRUNC | O_WRONLY, mode);
}
# else
#  warning Unsupported platform: creat() is missing
int creat(const char * filename, mode_t mode)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif


/* fcntl */
#ifndef SYS_fcntl
# warning Unsupported platform: fcntl() is missing
int fcntl(int fd, int cmd, ...)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* flock */
#ifndef SYS_flock
# warning Unsupported platform: flock() is missing
int flock(int fd, int operation)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* open */
#ifndef SYS_open
# warning Unsupported platform: open() is missing
int open(char const * filename, int flags, ...)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* openat */
#ifndef SYS_openat
# warning Unsupported platform: openat() is missing
int openat(int fd, char const * filename, int flags, ...)
{
	errno = ENOSYS;
	return -1;
}
#endif
