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



_start:
	/* terminate stack */
	mov	%g0, %fp
	sub	%sp, 0x18, %sp

	/* argc, argv, arge, environ */
	ld	[%sp+0x58], %o0		/* argc, really is [%sp+0x40] */
	add	%sp, 0x5c, %o1		/* argv, really is [%sp+0x44] */
	add	%o1, %o0, %o2		/* arge = 4 * (argv + argc + 1) */
	add	%o2, %o0, %o2
	add	%o2, %o0, %o2
	add	%o2, %o0, %o2
	add	%o2, 0x4, %o2
	sethi	%hi(environ), %o3	/* %o3 = &environ */
	or	%o3, %lo(environ), %o3
	st	%o2, [%o3]		/* *environ = %o2 */

	/* main */
	call	main
	nop

	/* exit */
	call	exit
	mov	%i0, %o0

	/* crash */
	ret
	nop


/* other essential functions */
/* udiv */
.global .udiv
.udiv:
	ret
	udivcc	%o0, %o1, %o0


/* umul */
.global .umul
.umul:
	ret
	umulcc	%o0, %o1, %o0
