/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



_start:
	/* terminate stack */
	mov	%g0, %fp

	/* argc, argv, arge, environ */
	/* %sp is 0xefffec48, argc is 0xefffec88, argv is 0xefffed3c */
	ld	[%sp+0x40], %o0		/* argc */
	add	%sp, 0x44, %o1		/* argv */
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


/* other essential sections */
.section ".note.netbsd.ident", "a"
	.p2align 2

	.long	7
	.long	4
	.long	1
	.ascii	"NetBSD\0\0"
	.long	300000000
	.previous
	.p2align 2
