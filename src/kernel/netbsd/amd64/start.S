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
	pop	%rax		/* argc		*/
	mov	%rsp, %rbx	/* argv		*/
	push	%rax
	mov	%rbx, %rcx	/* envp		*/
	add	$8, %rcx
	add	%rax, %rcx
	add	%rax, %rcx
	add	%rax, %rcx
	add	%rax, %rcx
	add	%rax, %rcx
	add	%rax, %rcx
	add	%rax, %rcx
	add	%rax, %rcx
#ifdef PIC			/* environ	*/
	mov	%rcx, environ@GOT(%rip)
#else
	mov	%rcx, environ
#endif
	xor	%rbp, %rbp	/* stack	*/
	mov	%rax, %rdi	/* main		*/
	mov	%rbx, %rsi
	mov	%rcx, %rdx
	call	main
	mov	%rax, %rdi	/* exit		*/
	push	%rax
	call	exit
	hlt
