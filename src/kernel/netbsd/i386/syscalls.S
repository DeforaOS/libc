/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */
/* FIXME:
 * - some syscalls may return an additional value into %edx (eg lseek)
 * - ftruncate() and truncate() probably need a wrapper (for padding) */



_syscall:
	int	$0x80
	jnc	.errnoret
.errno:
	mov	%eax, errno
	mov	$-1, %eax
.errnoret:
	ret


/* macros */
#define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %eax; \
	jmp	_syscall


/* functions */
/* _brk */
.global _brk
.type _brk,@function
_brk:
	mov	$SYS_brk, %eax
	int	$0x80
	jc	.errno
	ret
#undef SYS_brk


/* _exit */
.global _exit
.type _exit,@function
_exit:
	mov	$SYS_exit, %eax
	jmp	_syscall


/* execve */
.global execve
.type execve,@function
execve:
	mov	$SYS_execve, %eax
	int	$0x80
	mov	%eax, errno
	mov	$-1, %eax
	ret
#undef SYS_execve


/* longjmp */
/* XXX from NetBSD's libc without PIC prologue/epilogue */
.global longjmp
.type longjmp,@function
longjmp:
	mov	4(%esp), %ecx
	lea	24(%ecx), %edx

	push	$0
	push	%edx
	push	$3			/* SIG_SETMASK */
	call	sigprocmask
	add	$12, %esp

	mov	4(%esp), %edx
	mov	8(%esp), %eax
	mov	0(%edx), %ecx
	mov	4(%edx), %ebx
	mov	8(%edx), %esp
	mov	12(%edx), %ebp
	mov	16(%edx), %esi
	mov	20(%edx), %edi
	test	%eax, %eax
	jnz	1f
	incl	%eax
1:	mov	%ecx, 0(%esp)
	ret


/* pipe */
.global pipe
.type pipe,@function
pipe:
	mov	$SYS_pipe, %eax
	int	$0x80
	jc	.errno
	mov	4(%esp), %ecx
	mov	%eax, (%ecx)
	mov	%edx, 4(%ecx)
	mov	$0, %eax
	ret
#undef SYS_pipe


/* setjmp */
/* XXX from NetBSD's libc without PIC prologue/epilogue */
.global setjmp
.type setjmp,@function
setjmp:
	mov	4(%esp), %ecx
	mov	0(%esp), %edx
	mov	%edx, 0(%ecx)
	mov	%ebx, 4(%ecx)
	mov	%esp, 8(%ecx)
	mov	%ebp, 12(%ecx)
	mov	%esi, 16(%ecx)
	mov	%edi, 20(%ecx)

	lea	24(%ecx), %edx

	push	%edx
	push	$0
	push	$0
	call	sigprocmask
	add	$12, %esp

	mov	$0, %eax
	ret
