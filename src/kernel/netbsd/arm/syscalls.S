/* $Id$ */
/* Copyright (c) 2009-2020 Pierre Pronchery <khorben@defora.org> */
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



_syscall:
	/* svc	0x00000000 */
	mov	%r7, %ip
	cmp	%r0, #0
	bge	.errnoret
	mov	%r1, #0
	sub	%r0, %r1, %r0
	ldr	%r1, =errno
	str	%r0, [%r1]
	mov	%r0, #-1
.errnoret:
	mov	%pc, %lr


/* macros */
#define SYSCALL(name) \
.global name; \
.type _start, %function; \
name:; \
	mov	%ip, %r7; \
	ldr	%r7, =SYS_ ## name; \
	b	_syscall;


/* functions */
/* _brk */
.global _brk
_brk:
	mov	%ip, %r7
	ldr	%r7, =SYS_brk
	b	_syscall
#undef SYS_brk


/* _exit */
.global _exit
_exit:
	mov	%ip, %r7
	ldr	%r7, =SYS_exit
	b	_syscall
