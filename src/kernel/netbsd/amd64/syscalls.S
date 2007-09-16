/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
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



_syscall:
	syscall
	jnc	.errnoret
.errno:
	mov	%rax, errno@GOT(%rip)
	mov	$-1, %rax
.errnoret:
	ret


/* macros */
#define SYSCALL(name) \
.global name; \
name:; \
	mov	$SYS_ ## name, %rax; \
	jmp	_syscall


/* functions */
/* _brk */
.global _brk
_brk:
	mov	$SYS_brk, %rax
	syscall
	jc	.errno
	ret
#undef SYS_brk

/* _exit */
.global _exit
_exit:
	mov	$SYS_exit, %rax
	jmp	_syscall

/* execve */
.global execve
execve:
	mov	$SYS_execve, %rax
	syscall
	mov	%rax, errno@GOT(%rip)
	mov	$-1, %rax
	ret
#undef SYS_execve
