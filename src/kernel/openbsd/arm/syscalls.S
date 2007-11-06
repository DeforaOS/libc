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
	swi
	/* FIXME implement
	bcc	.errnoret
	set	errno, %g1
	st	%o0, [%g1]
	set	-1, %o0
.errnoret: */
	mov	%pc, %lr


/* macros */
#define SYSCALL(name) \
.global name; \
name:; \
	ldr	%ip, =SYS_ ## name; \
	b	_syscall;


/* functions */
/* _brk */
.global _brk
_brk:
	ldr	%ip, =SYS_brk
	b	_syscall
#undef SYS_brk

/* _exit */
.global _exit
_exit:
	ldr	%ip, =SYS_exit
	b	_syscall
