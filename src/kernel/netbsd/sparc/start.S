/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



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
	ret
	udivcc	%o0, %o1, %o0


/* umul */
.global .umul
.umul:
	ret
	umulcc	%o0, %o1, %o0
