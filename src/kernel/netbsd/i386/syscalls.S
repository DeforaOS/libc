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
