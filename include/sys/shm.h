/* $Id$ */
/* Copyright (c) 2008-2016 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SYS_SHM_H
# define LIBC_SYS_SHM_H

# include "../compat.h"
# include "../compat/sys/shm.h"
# include "ipc.h"


/* types */
# ifndef pid_t
#  define pid_t pid_t
typedef __pid_t pid_t;
# endif
# ifndef size_t
#  define size_t size_t
typedef __size_t size_t;
# endif
# ifndef smhid_ds
#  define shmid_ds shmid_ds
struct shmid_ds
{
	/* FIXME implement */
};
# endif


/* constants */
# define SHM_RDONLY		010000


/* functions */
void * shmat(int shmid, const void * shmaddr, int shmflag);
int shmctl(int shmid, int cmd, struct shmid_ds * buf);
int shmdt(const void * shmaddr);
int shmget(key_t key, size_t size, int shmflag);

#endif /* !LIBC_SYS_SHM_H */
