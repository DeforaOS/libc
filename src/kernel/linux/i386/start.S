/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



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
	push	%eax
	call	exit
	hlt
