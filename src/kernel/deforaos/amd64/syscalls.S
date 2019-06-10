/* $Id$ */
/* Copyright (c) 2019 Pierre Pronchery <khorben@defora.org> */
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



#include "kernel/deforaos/errno.h"


/* macros */
#ifndef SYSCALL
# ifdef __PIC__
#  define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	errno@GOTPCREL(%rip), %rcx; \
	mov	$ENOSYS, (%rcx); \
	mov	$-1, %rax; \
	ret
# else
#  define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	movl	$ENOSYS, errno; \
	mov	$-1, %rax; \
	ret
# endif
#endif


/* functions */
/* _brk */
.global _brk
.type _brk,@function
_brk:
	xor	%rax, %rax
	ret
#undef SYS_brk


/* _exit */
.global _exit
.type _exit,@function
_exit:
	/* infinite loop */
	cli
1:	hlt
	jmp	1b


/* write */
.global write
.type write,@function
write:
	push	%rdx
	push	%rdx
	push	%rsi
	push	%rdi
#ifdef __PIC__
	call	console_get_default@PLT
#else
	call	console_get_default
#endif
	pop	%rdi
	pop	%rsi
	pop	%rdx
	mov	%rax, %rdi
#ifdef __PIC__
	call	console_print@PLT
#else
	call	console_print
#endif
	pop	%rax
	ret
#undef SYS_write
