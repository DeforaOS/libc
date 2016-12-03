/* $Id$ */
/* Copyright (c) 2016 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_SYS_MSG_H
# define LIBC_SYS_MSG_H

# include "ipc.h"
# include "../compat.h"
# include "../compat/sys/msg.h"


/* types */
# ifndef pid_t
#  define pid_t pid_t
typedef signed int pid_t;
# endif
# ifndef size_t
#  define size_t __size_t
# endif
# ifndef ssize_t
#  define ssize_t __ssize_t
# endif
# ifndef msqid_ds
#  define msqid_ds msqid_ds
#  warning Unsupported platform: struct msqid_ds is missing
struct msqid_ds;
# endif


/* functions */
int msgctl(int msqid, int cmd, struct msqid_ds * buf);
int msgget(key_t key, int msgflg);
ssize_t msgrcv(int msqid, void * msgp, size_t msgsz, long msgtyp, int msgflg);
int msgsnd(int msqid, const void * msgp, size_t msgsz, int msgflg);

#endif /* !LIBC_SYS_MSG_H */
