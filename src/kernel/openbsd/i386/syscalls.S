/* $Id$ */
/* Copyright (c) 2007-2016 Pierre Pronchery <khorben@defora.org> */
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
/* FIXME:
 * - some syscalls may return an additional value into %edx (eg lseek) */



_syscall:
	int	$0x80
	jnc	.errnoret
.errno:
	mov	%eax, errno
	mov	$-1, %eax
.errnoret:
	ret


/* macros */
#ifndef SYSCALL
# define SYSCALL(name) \
.global name; \
name:; \
	mov	$SYS_ ## name, %eax; \
	jmp	_syscall
#endif


/* functions */
/* _brk */
.global _brk
_brk:
	mov	$SYS_brk, %eax
	int	$0x80
	jc	.errno
	ret
#undef SYS_brk

/* _exit */
.global _exit
_exit:
	mov	$SYS_exit, %eax
	jmp	_syscall

/* execve */
.global execve
execve:
	mov	$SYS_execve, %eax
	int	$0x80
	mov	%eax, errno
	mov	$-1, %eax
	ret
#undef SYS_execve
