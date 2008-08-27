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



.weak exit				/* apparently necessary */


_start:
.type _start,#function
	/* terminate stack */
	mov	fp, $0

	/* argc, argv, arge */
	ldr	r0, [sp]		/* argc */
	add	r1, sp, $4		/* argv */
	add	r2, r0, $1		/* arge */
	add	r2, r2, r2
	add	r2, r2, r2
	/* FIXME implement environ */

	/* main */
	bl	main

	/* exit */
	bl	exit

exit:
	/* crash */
	mov	%pc, %lr
