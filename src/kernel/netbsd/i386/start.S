/* $Id$ */
/* Copyright (c) 2006-2017 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



_start:
	/* reset the stack */
	xor	%ebp, %ebp

	/* setup the environment */
	mov	(%esp), %eax	/* argc */
	mov	%esp, %ebx	/* argv */
	add	$0x4, %ebx
	mov	%eax, %ecx	/* envp */
	inc	%ecx
	shl	$2, %ecx
	add	%ebx, %ecx
	mov	%ecx, environ	/* environ */
#if defined(__ELF__)
	mov	%ecx, %edx	/* auxv */
auxv:
	cmpl	$0x0, (%edx)
	jz	auxv_done
	add	$0x4, %edx
	jmp	auxv
auxv_done:
	add	$0x4, %edx
	push	%edx
#endif
	push	%ecx
	push	%ebx
	push	%eax
#if defined(__ELF__)
	push	%edx
#endif

#if defined(__SSP__)
	/* initialize SSP */
	call	__stack_chk_setup
#endif

#if defined(__ELF__)
	/* initialize dlfcn */
	call	__start_dlfcn
	add	$0x4, %esp
#endif

	/* initialize stdio */
	call	__start_stdio

	/* call the global constructors */
	call	_init

	/* run the program */
	call	main
#if defined(__ELF__)
	add	$0x10, %esp
#else
	add	$0xc, %esp
#endif
	push	%eax

	/* call the global destructors */
	call	_fini

	/* exit the program */
	call	exit
	add	$0x4, %esp

	hlt
