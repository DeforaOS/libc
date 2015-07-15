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



#include "errno.h"
#include "../syscalls.h"
#include "sys/resource.h"


/* functions */
/* getpriority */
#ifndef SYS_getpriority
# warning Unsupported platform: getpriority() is missing
int getpriority(int which, id_t who)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* getrlimit */
#ifndef SYS_getrlimit
# warning Unsupported platform: getrlimit() is missing
int getrlimit(int resource, struct rlimit * rlp)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* getrusage */
#ifndef SYS_getrusage
# warning Unsupported platform: getrusage() is missing
int getrusage(int who, struct rusage * rup)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* setpriority */
#ifndef SYS_setpriority
# warning Unsupported platform: setpriority() is missing
int setpriority(int which, id_t who, int value)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* setrlimit */
#ifndef SYS_setrlimit
# warning Unsupported platform: setrlimit() is missing
int setrlimit(int resource, const struct rlimit * rlp)
{
	errno = ENOSYS;
	return -1;
}
#endif
