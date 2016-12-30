/* $Id$ */
/* Copyright (c) 2012-2016 Pierre Pronchery <khorben@defora.org> */
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



.text


/* FreeBSD, Linux, NetBSD, OpenBSD */
#if defined(__FreeBSD__) || defined(__linux__) || defined(__NetBSD__) \
	|| defined(__OpenBSD__)
# if defined(__amd64__)
__syscall:
	push	%rdi
	push	%rsi
	push	%rax
	push	%rcx
	push	%rdx
	push	%r8
	push	%r9
	push	%r10
	push	%r11
	mov	%rdx, %rcx
	mov	%rsi, %rdx
	mov	%rdi, %rsi
	mov	%rax, %rdi
	call	analyze@PLT
	pop	%r11
	pop	%r10
	pop	%r9
	pop	%r8
	pop	%rdx
	pop	%rcx
	pop	%rax
	pop	%rsi
	pop	%rdi
	jmp	_syscall@PLT

#  define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %rax; \
	jmp	__syscall@PLT
# elif defined(__i386__)
__syscall:
	push	%eax
	/* FIXME also implement further parameters */
	call	analyze
	pop	%eax
	jmp	_syscall

#  define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %eax; \
	jmp	__syscall
# else
#  warning Unsupported architecture
# endif
#else
# warning Unsupported platform
#endif

#include "../src/syscalls.S"


/* platform-specific fixes */
/* NetBSD */
#if defined(__NetBSD__)
# if defined(__amd64__)
/* fstat */
.global __fstat50
.type __fstat50,@function
__fstat50:
	mov	$SYS_fstat, %rax
	jmp	__syscall@PLT

/* lstat */
.global __lstat50
.type __lstat50,@function
__lstat50:
	mov	$SYS_lstat, %rax
	jmp	__syscall@PLT

/* stat */
.global __stat50
.type __stat50,@function
__stat50:
	mov	$SYS_stat, %rax
	jmp	__syscall@PLT
# elif defined(__i386__)
/* fstat */
.global __fstat50
.type __fstat50,@function
__fstat50:
	mov	$SYS_fstat, %eax
	jmp	__syscall

/* lstat */
.global __lstat50
.type __lstat50,@function
__lstat50:
	mov	$SYS_lstat, %eax
	jmp	__syscall

/* stat */
.global __stat50
.type __stat50,@function
__stat50:
	mov	$SYS_stat, %eax
	jmp	__syscall
# endif
#endif
