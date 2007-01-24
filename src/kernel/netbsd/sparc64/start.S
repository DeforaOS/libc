/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



_start:
	/* terminate stack */
	mov	%g0, %fp

	/* argc, argv, arge, environ */
	ldx	[%sp+0x87f], %o0	/* argc */
	add	%sp, 0x887, %o1		/* argv */
	umul	%o0, 0x8, %o2
	add	%o1, %o2, %o2
	add	%o2, 0x8, %o2
	set	environ, %o3		/* %o3 = &environ */
	stx	%o2, [%o3]		/* *environ = %o2 */

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
