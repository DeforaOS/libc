/* $Id$ */
/* Copyright (c) 2016-2017 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_OPENBSD_SYS_MSG_H
# define LIBC_KERNEL_OPENBSD_SYS_MSG_H


/* types */
# ifndef msqid_ds
#  define msqid_ds msqid_ds
struct msqid_ds
{
	struct ipc_perm msg_perm;
	struct msg * __padding1;
	struct msg * __padding2;
	unsigned long msg_cbytes;
	unsigned long msg_qnum;
	unsigned long msg_qbytes;
	pid_t msg_lspid;
	pid_t msg_lrpid;
	time_t msg_stime;
	long __padding3;
	time_t msg_rtime;
	long __padding4;
	time_t msg_ctime;
	long __padding5;
	long __padding6[4];
};
# endif


/* constants */
# define MSG_NOERROR	010000

#endif /* !LIBC_KERNEL_OPENBSD_SYS_MSG_H */
