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



#ifndef LIBC_KERNEL_NETBSD_SYS_VT_H
# define LIBC_KERNEL_NETBSD_SYS_VT_H


/* types */
struct vt_mode
{
	char mode;
	char waitv;
	short relsig;
	short acqsig;
	short frsig;
};

typedef struct vt_mode vtmode_t;

struct vt_stat
{
	unsigned short v_active;
	unsigned short v_signal;
	unsigned short v_state;
};


/* constants */
# define VT_FALSE		0
# define VT_TRUE		1
# define VT_ACKACQ		2

# define VT_PROCESS		1

# define VT_ACTIVATE		0x20007605
# define VT_GETACTIVE		0x40047607
# define VT_GETMODE		0x40087603
# define VT_GETSTATE		0x40067664
# define VT_RELDISP		0x20007604
# define VT_SETMODE		0x80087602
# define VT_OPENQRY		0x40047601
# define VT_WAITACTIVE		0x20007606

#endif /* !LIBC_KERNEL_NETBSD_SYS_VT_H */
