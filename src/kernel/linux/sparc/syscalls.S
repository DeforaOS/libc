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



_syscall0:
	jmp	.trap
	nop

_syscall1:
	mov	%i1, %o0
	jmp	.trap
	nop

_syscall2:
	mov	%i2, %o1
	jmp	.trap
	nop

_syscall3:
	mov	%i3, %o2
	jmp	.trap
	nop

_syscall4:
	mov	%i4, %o3
	jmp	.trap
	nop

_syscall5:
	mov	%i5, %o4
	jmp	.trap
	nop

_syscall6:
	/* FIXME how to get the last arg? */

.trap:
	mov	%i0, %g1	/* syscall number */
	ta	8
	/* FIXME errno */
	ret
	nop
