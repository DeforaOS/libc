/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



/* FIXME implement */
_start:
	/* terminate stack */

	/* argc, argv, arge, environ */

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
