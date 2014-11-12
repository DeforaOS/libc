/* $Id$ */
/* Copyright (c) 2005-2014 Pierre Pronchery <khorben@defora.org> */
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
#include "sys/mman.h"


/* mlock */
#ifndef SYS_mlock
# warning Unsupported platform: mlock() is missing
int mlock(const void * addr, size_t length)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* mmap */
#ifndef SYS_mmap
# warning Unsupported platform: mmap() is missing
void * mmap(void * addr, size_t length, int prot, int flags, int fd,
		off_t offset)
{
	errno = ENOSYS;
	return MAP_FAILED;
}
#endif


/* mprotect */
#ifndef SYS_mprotect
# warning Unsupported platform: mprotect() is missing
int mprotect(void * addr, size_t length, int prot)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* munlock */
#ifndef SYS_munlock
# warning Unsupported platform: munlock() is missing
int munlock(const void * addr, size_t length)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* munmap */
#ifndef SYS_munmap
# warning Unsupported platform: munmap() is missing
int munmap(void * addr, size_t length)
{
	errno = ENOSYS;
	return -1;
}
#endif
