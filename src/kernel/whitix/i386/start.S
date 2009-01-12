/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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
	pop	%eax		/* argc */
	mov	%esp, %ebx	/* argv */
	push	%eax
	mov	%ebx, %ecx	/* envp */
	add	$4, %ecx
	add	%eax, %ecx
	add	%eax, %ecx
	add	%eax, %ecx
	add	%eax, %ecx
	xor	%ebp, %ebp	/* stack */
	push	%ebp
	push	%esp
	mov	%esp, %ebp
	push	%ecx		/* main */
	push	%ebx
	push	%eax
	call	main
	push	%eax
	call	exit
	hlt
