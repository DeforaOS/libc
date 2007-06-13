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

	/* argc, argv, arge, environ */
	/* %sp is 0xefffec48, argc is 0xefffec88, argv is 0xefffed3c */
	ld	[%sp+0x40], %o0		/* argc */
	add	%sp, 0x44, %o1		/* argv */
	add	%o0, %o1, %o2		/* arge = 4 * (argv + argc + 1) */
	add	%o0, %o2, %o2
	add	%o0, %o2, %o2
	add	%o0, %o2, %o2
	add	%o2, 0x4, %o2
	set	environ, %o3		/* %o3 = &environ */
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
	retl
	udivcc	%o0, %o1, %o0


/* umul */
.global .umul
.umul:
	retl
	umulcc	%o0, %o1, %o0


/* urem */
.global .urem
.urem:
	udivcc	%o0, %o1, %o2		/* c = a / b */
	umulcc	%o1, %o2, %o1		/* b = b * c */
	retl
	subcc	%o0, %o1, %o0		/* a = a - b */
