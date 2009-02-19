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



_start:
	pop	%rdi		/* argc		*/
	mov	%rsp, %rsi	/* argv		*/
	push	%rdi
	mov	%rdi, %rdx	/* envp		*/
	shl	$3, %rdx
	add	$8, %rdx
	add	%rsi, %rdx
#ifdef PIC			/* environ	*/
	mov	%rdx, environ@GOTPCREL(%rip)
#else
	mov	%rdx, environ
#endif
	xor	%rbp, %rbp	/* stack	*/
#ifdef PIC
	call	main@GOTPCREL(%rip)
#else
	call	main
#endif
	mov	%rax, %rdi	/* exit		*/
#ifdef PIC
	call	exit@GOTPCREL(%rip)
#else
	call	exit
#endif
	hlt
