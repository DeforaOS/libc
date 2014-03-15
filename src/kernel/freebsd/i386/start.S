/* $Id$ */
/* Copyright (c) 2008-2014 Pierre Pronchery <khorben@defora.org> */
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
/* FIXME:
   - directly taken from the one for NetBSD */



_start:
	pop	%eax		/* argc */
	mov	%esp, %ebx	/* argv */
	push	%eax
	mov	%ebx, %ecx	/* envp */
	add	$4, %ecx
	add	%eax, %ecx
	add	%eax, %ecx
	add	%eax, %ecx
	add	%eax, %ecx
	mov	%ecx, environ	/* environ */
	xor	%ebp, %ebp	/* stack */
	push	%ebp
	push	%esp
	mov	%esp, %ebp
	push	%ecx		/* main */
	push	%ebx
	push	%eax
	call	main
	push	%eax		/* exit */
	call	exit
	hlt
