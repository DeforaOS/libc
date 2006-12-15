/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#if defined(NETBSD_USE_LINUX_EMULATION)
_start:
	pop	%ecx		/* argc */
	mov	%esp, %ebx	/* argv */
	mov	%esp, %eax	/* envp */
	add	$4, %eax
	add	%ecx, %eax
	add	%ecx, %eax
	add	%ecx, %eax
	add	%ecx, %eax
	mov	%eax, environ
	xor	%ebp, %ebp	/* stack */
	push	%ebp
	push	%ebp
	push	%ebp
	mov	%esp, %ebp
	push	%eax
	push	%ebx
	push	%ecx
	call	main
	push	%eax
	call	exit
	hlt
#endif
