/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



_start:
	/* terminate the stack frame */
	mov	%g0, %fp
	sub	%sp, 0x18, %sp

	/* argc, argv */
	ld	[%sp+0x58], %o0		/* argc, really is [%sp+0x40] */
	add	%sp, 0x5c, %o1		/* argv, really is [%sp+0x44] */

	/* environ */
	add	%o1, %o0, %o2
	add	%o2, %o0, %o2
	add	%o2, %o0, %o2
	add	%o2, %o0, %o2
	add	%o2, 4, %o2
	sethi	%hi(environ), %o3
	or	%o3, %lo(environ), %o3
	st	%o2, [%o3]		/* environ = [%o2] */

	/* main */
	call	main
	nop

	/* exit */
	call	exit
	mov	%o0, %i0

	/* die */
	ret
	nop
