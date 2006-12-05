/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "common.h"


.section .text
.global _start


#if defined(__linux__)
# if defined(__i386__)
_start:
	pop	%ecx		/* argc */
	mov	%esp, %ebx	/* argv */
	mov	%esp, %eax	/* envp */
	add	$4, %eax
	add	%ecx, %eax
	add	%ecx, %eax
	add	%ecx, %eax
	add	%ecx, %eax
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
# else /* linux !i386 */
#  warning Unsupported Linux port
# endif
#else /* !linux */
# warning Unsupported system
#endif
