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
