/* $Id$ */
/* Copyright (c) 2007-2014 Pierre Pronchery <khorben@defora.org> */
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

	/* initialize stdio */
	call	__start_stdio
	nop

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
