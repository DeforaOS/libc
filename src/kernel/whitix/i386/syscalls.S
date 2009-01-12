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



_syscall:
	mov	%ebp, %edx
	add	$4, %edx
	int	$0x30
.errno:
	cmp	$0, %eax
	jge	.errnoret
	neg	%eax
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
	mov	$SYSL_ ## name, %ecx; \
	jmp	_syscall


/* functions */
/* _exit */
.global _exit
.type _exit,@function
_exit:
	mov	$SYS_exit, %eax
	mov	$SYSL_exit, %ecx
	jmp	_syscall


/* _sbrk */
.global _sbrk
.type _sbrk,@function
_sbrk:
	mov	$SYS_sbrk, %eax
	mov	$SYSL_sbrk, %ecx
	jmp	_syscall
#undef SYS_sbrk
