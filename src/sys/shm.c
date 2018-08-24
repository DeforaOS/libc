/* $Id$ */
/* Copyright (c) 2008-2018 Pierre Pronchery <khorben@defora.org> */
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
#include "sys/shm.h"


#ifdef SYS__ipc
extern long _ipc(int cmd, ...);
#endif


/* functions */
/* shmat */
#ifndef SYS_shmat
# if defined(SYS__ipc) && defined(__IPC_SHMAT)
void * shmat(int shmid, const void * shmaddr, int shmflag)
{
	return (void *)_ipc(__IPC_SHMAT, shmid, shmaddr, shmflag);
}
# else
#  warning Unsupported platform: shmat() is missing
void * shmat(int shmid, const void * shmaddr, int shmflag)
{
	/* FIXME this return value may be considered legitimate */
	errno = ENOSYS;
	return NULL;
}
# endif
#endif


/* shmctl */
#ifndef SYS_shmctl
# if defined(SYS__ipc) && defined(__IPC_SHMCTL)
int shmctl(int shmid, int cmd, struct shmid_ds * buf)
{
	return _ipc(__IPC_SHMCTL, shmid, cmd, buf);
}
# else
#  warning Unsupported platform: shmctl() is missing
int shmctl(int shmid, int cmd, struct shmid_ds * buf)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif


/* shmdt */
#ifndef SYS_shmdt
# if defined(SYS__ipc) && defined(__IPC_SHMDT)
int shmdt(const void * shmaddr)
{
	return _ipc(__IPC_SHMDT, shmaddr);
}
# else
#  warning Unsupported platform: shmdt() is missing
int shmdt(const void * shmaddr)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif


/* shmget */
#ifndef SYS_shmget
# if defined(SYS__ipc) && defined(__IPC_SHMGET)
int shmget(key_t key, size_t size, int shmflag)
{
	return _ipc(__IPC_SHMGET, key, size, shmflag);
}
# else
#  warning Unsupported platform: shmget() is missing
int shmget(key_t key, size_t size, int shmflag)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif
