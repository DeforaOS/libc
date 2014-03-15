/* $Id$ */
/* Copyright (c) 2007-2014 Pierre Pronchery <khorben@defora.org> */
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
