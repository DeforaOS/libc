/* $Id$ */
/* Copyright (c) 2009-2015 Pierre Pronchery <khorben@defora.org> */
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



#include "kernel/linux/errno.h"


_syscall:
	mov	%rcx, %r10
	syscall
	cmp	$0, %rax
	jge	_syscall_return
	cmp	$-4096, %rax
	jle	_syscall_return
.errno:
	neg	%rax
#ifdef PIC
	mov	errno@GOTPCREL(%rip), %rcx
	mov	%rax, (%rcx)
#else
	mov	%rax, errno
#endif
	mov	$-1, %rax
_syscall_return:
	ret


/* macros */
#ifdef PIC
# define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %rax; \
	jmp	_syscall@PLT
#else
# define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %rax; \
	jmp	_syscall
#endif


/* functions */
/* _brk */
.global _brk
.type _brk,@function
_brk:
	mov	$SYS_brk, %rax
	syscall
	test	%rdi, %rax
	je	_brk_return
	mov	$-ENOMEM, %rax
	jmp	.errno
_brk_return:
	mov	$0, %rax
	ret
#undef SYS_brk


/* _exit */
.global _exit
.type _exit,@function
_exit:
	mov	$SYS_exit, %rax
#ifdef PIC
	jmp	_syscall@PLT
#else
	jmp	_syscall
#endif


/* execve */
.global execve
.type execve,@function
execve:
	mov	$SYS_execve, %rax
	syscall
	neg	%rax
#ifdef PIC
	mov	errno@GOTPCREL(%rip), %rcx
	mov	%rax, (%rcx)
#else
	mov	%rax, errno
#endif
	mov	$-1, %rax
	ret
#undef SYS_execve


/* _longjmp */
.global _longjmp
.type _longjmp,@function
_longjmp:
	/* restore registers */
	mov	64(%rdi), %r15			/* %r15 */
	mov	56(%rdi), %r14			/* %r14 */
	mov	48(%rdi), %r13			/* %r13 */
	mov	40(%rdi), %r12			/* %r12 */
	mov	32(%rdi), %r11			/* %r11 */
	mov	24(%rdi), %rbp			/* base pointer */
	mov	16(%rdi), %rsp			/* stack pointer */
	mov	8(%rdi), %rbx
	mov	0(%rdi), %rdx			/* return address */
	mov	%rdx, 0(%rsp)

	/* if(val != 0) goto __longjmp_return; else val++ */
	mov	%esi, %eax
	test	%eax, %eax
	jnz	__longjmp_return
	inc	%eax

	/* return val */
__longjmp_return:
	ret


/* longjmp */
.global longjmp
.type longjmp,@function
longjmp:
.global siglongjmp
.type siglongjmp,@function
siglongjmp:
	/* if(env[9] == 0) goto _longjmp_registers */
	mov	72(%rdi), %rdx
	test	%rdx, %rdx
	jz	_longjmp_registers

	/* restore the signal mask */
	/* sigprocmask(SIG_SETMASK, &env[10], NULL) */
	push	%rdi
	push	%rsi
	lea	80(%rdi), %rdx
	mov	$0x0, %rsi
	mov	$0x2, %rdi
#ifdef PIC
	call	sigprocmask@PLT
#else
	call	sigprocmask
#endif
	pop	%rsi
	pop	%rdi

	/* restore registers */
_longjmp_registers:
	mov	64(%rdi), %r15			/* %r15 */
	mov	56(%rdi), %r14			/* %r14 */
	mov	48(%rdi), %r13			/* %r13 */
	mov	40(%rdi), %r12			/* %r12 */
	mov	32(%rdi), %r11			/* %r11 */
	mov	24(%rdi), %rbp			/* base pointer */
	mov	16(%rdi), %rsp			/* stack pointer */
	mov	8(%rdi), %rbx
	mov	0(%rdi), %rdx			/* return address */
	mov	%rdx, 0(%rsp)

	/* if(val != 0) goto _longjmp_return; else val++ */
	mov	%esi, %eax
	test	%eax, %eax
	jnz	_longjmp_return
	inc	%eax

	/* return val */
_longjmp_return:
	ret


/* lseek */
.global lseek
.type lseek,@function
lseek:
	mov	%rdx, %rcx
	mov	%rsi, %rdx
	mov	$0, %rsi
	mov	$SYS_lseek, %rax
	jmp	_syscall
#undef SYS_lseek


/* pipe */
.global pipe
.type pipe,@function
pipe:
	mov	$SYS_pipe, %rax
	mov	%rcx, %r10
	syscall
	jc	.errno
	mov	%eax, (%rdi)
	mov	%edx, 4(%rdi)
	mov	$0, %rax
	ret
#undef SYS_pipe


/* _setjmp */
.global _setjmp
.type _setjmp,@function
_setjmp:
	/* save registers */
	mov	0(%rsp), %rsi			/* return address */
	mov	%rsi, 0(%rdi)
	mov	%rbx, 8(%rdi)			/* %rbx */
	mov	%rsp, 16(%rdi)			/* stack pointer */
	mov	%rbp, 24(%rdi)			/* base pointer */
	mov	%r11, 32(%rdi)			/* %r11 */
	mov	%r12, 40(%rdi)			/* %r12 */
	mov	%r13, 48(%rdi)			/* %r13 */
	mov	%r14, 56(%rdi)			/* %r14 */
	mov	%r15, 64(%rdi)			/* %r15 */

	/* the signal mask is not saved */
	/* env[9] = 0 */
	movq	$0x0, 72(%rdi)

	/* return 0 */
	mov	$0x0, %eax
	ret


/* setjmp */
.global setjmp
.type setjmp,@function
setjmp:
	/* save registers */
	mov	0(%rsp), %rsi			/* return address */
	mov	%rsi, 0(%rdi)
	mov	%rbx, 8(%rdi)			/* %rbx */
	mov	%rsp, 16(%rdi)			/* stack pointer */
	mov	%rbp, 24(%rdi)			/* base pointer */
	mov	%r11, 32(%rdi)			/* %r11 */
	mov	%r12, 40(%rdi)			/* %r12 */
	mov	%r13, 48(%rdi)			/* %r13 */
	mov	%r14, 56(%rdi)			/* %r14 */
	mov	%r15, 64(%rdi)			/* %r15 */

	/* the signal mask is not saved yet */
	/* env[9] = 0 */
	movq	$0x0, 72(%rdi)

	/* res = sigprocmask(0, NULL, &env[9]) */
	push	%rdi
	mov	$0x0, %rdi
	mov	$0x0, %rsi
	lea	80(%rax), %rdx
#ifdef PIC
	call	sigprocmask@PLT
#else
	call	sigprocmask
#endif
	pop	%rdi

	/* the signal mask was saved */
	/* if(res == 0) env[9] = 1 */
	test	%eax, %eax
	jnz	_setjmp_return
	movq	$0x1, 72(%rdi)

	/* return 0 */
_setjmp_return:
	mov	$0x0, %eax
	ret


/* sigsetjmp */
.global sigsetjmp
.type sigsetjmp,@function
sigsetjmp:
	/* if(savemask == 0) return _setjmp() */
	test	%esi, %esi
	jnz	_sigsetjmp_save
#ifdef PIC
	jmp	_setjmp@PLT
#else
	jmp	_setjmp
#endif
_sigsetjmp_save:
	/* else return setjmp() */
#ifdef PIC
	jmp	setjmp@PLT
#else
	jmp	setjmp
#endif
