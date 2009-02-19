/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



.weak exit				/* apparently necessary */
.extern environ


_start:
.type _start,#function
	/* terminate stack */
	mov	%fp, $0

	/* argc, argv, arge */
	ldr	%r0, [%sp]		/* argc */
	add	%r1, %sp, $4		/* argv */
	add	%r2, %r0, $1		/* arge */
	add	%r2, %r2, %r2
	add	%r2, %r2, %r2
	add	%r2, %r1, %r2
	ldr	%r3, =environ
	str	%r2, [%r3]

	/* main */
	bl	main

	/* exit */
	bl	exit

exit:
	/* crash */
	mov	%pc, %lr
