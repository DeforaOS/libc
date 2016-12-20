/* $Id$ */
/* Copyright (c) 2009-2016 Pierre Pronchery <khorben@defora.org> */
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
	xor	%rbp, %rbp	/* stack */

#if defined(__SSP__)
	/* initialize SSP */
# ifdef __PIC__
	call	__stack_chk_setup@PLT
# else
	call	__stack_chk_setup
# endif
#endif

	/* run the main program */
	mov	(%rsp), %rdi	/* argc */
	mov	%rsp, %rsi	/* argv */
	add	$8, %rsi
	mov	%rsi, %rdx	/* envp */
	add	$8, %rdx
#ifdef __PIC__			/* environ	*/
	mov	environ@GOTPCREL(%rip), %rcx
	mov	%rdx, (%rcx)
#else
	mov	%rdx, environ
#endif
#ifdef __PIC__
	call	main@PLT
#else
	call	main
#endif

	/* exit the main program */
	mov	%rax, %rdi
#ifdef __PIC__
	call	exit@PLT
#else
	call	exit
#endif
	hlt
