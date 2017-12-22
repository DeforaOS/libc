/* $Id$ */
/* Copyright (c) 2008-2016 Pierre Pronchery <khorben@defora.org> */
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



_syscall:
	mov	%rcx, %r10
	syscall
	jnc	_syscall_return
.errno:
#ifdef __PIC__
	mov	errno@GOTPCREL(%rip), %rcx
	mov	%rax, (%rcx)
#else
	mov	%rax, errno
#endif
	mov	$-1, %rax
_syscall_return:
	ret


/* macros */
#ifndef SYSCALL
# ifdef __PIC__
#  define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %rax; \
	jmp	_syscall@PLT
# else
#  define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %rax; \
	jmp	_syscall
# endif
#endif


/* functions */
/* _brk */
.global _brk
.type _brk,@function
_brk:
	mov	$SYS_brk, %rax
	syscall
	jc	.errno
	ret
#undef SYS_brk


/* _exit */
.global _exit
.type _exit,@function
_exit:
	mov	$SYS_exit, %rax
#ifdef __PIC__
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
#ifdef __PIC__
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

	mov	%esi, %eax			/* if(val != 0) */
	test	%eax, %eax
	jnz	__longjmp_return		/*   goto __longjmp_return */
	inc	%eax				/* val = 1 */

__longjmp_return:
	ret					/* return val */


/* longjmp */
.global longjmp
.type longjmp,@function
longjmp:
.global siglongjmp
.type siglongjmp,@function
siglongjmp:
	mov	72(%rdi), %rdx			/* if(env[9] == 0) */
	test	%rdx, %rdx
	jz	_longjmp_registers		/*   goto _longjmp_registers */

	/* restore the signal mask */
	/* sigprocmask(SIG_SETMASK, &env[10], NULL) */
	push	%rdi
	push	%rsi
	mov	$0x3, %rdi
	lea	80(%rdi), %rsi
	mov	$0x0, %rdx
#ifdef __PIC__
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

	mov	%esi, %eax			/* if(val != 0) */
	test	%eax, %eax
	jnz	_longjmp_return			/*   goto _longjmp_return */
	inc	%eax				/* else val = 1 */

_longjmp_return:
	ret					/* return val */


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


/* mmap */
.global mmap
.type mmap,@function
mmap:
	sub	$0x10, %rsp
	mov	%r9, 0x8(%rsp)
	mov	$0, %r9
	mov	$SYS_mmap, %rax
	mov	%rcx, %r10
	syscall
	add	$0x10, %rsp /* XXX clears carry flag? */
	jc	.errno
	ret
#undef SYS_mmap


/* pipe */
.global pipe
.type pipe,@function
pipe:
	mov	$SYS_pipe, %rax
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
	mov	0(%rsp), %rax			/* return address */
	mov	%rax, 0(%rdi)
	mov	%rbx, 8(%rdi)			/* %rbx */
	mov	%rsp, 16(%rdi)			/* stack pointer */
	mov	%rbp, 24(%rdi)			/* base pointer */
	mov	%r11, 32(%rdi)			/* %r11 */
	mov	%r12, 40(%rdi)			/* %r12 */
	mov	%r13, 48(%rdi)			/* %r13 */
	mov	%r14, 56(%rdi)			/* %r14 */
	mov	%r15, 64(%rdi)			/* %r15 */

	/* the signal mask is not saved */
	movq	$0x0, 72(%rdi)			/* env[9] = 0 */

	mov	$0x0, %eax			/* return 0 */
	ret


/* setjmp */
.global setjmp
.type setjmp,@function
setjmp:
	/* save registers */
	mov	0(%rsp), %rax			/* return address */
	mov	%rax, 0(%rdi)
	mov	%rbx, 8(%rdi)			/* %rbx */
	mov	%rsp, 16(%rdi)			/* stack pointer */
	mov	%rbp, 24(%rdi)			/* base pointer */
	mov	%r11, 32(%rdi)			/* %r11 */
	mov	%r12, 40(%rdi)			/* %r12 */
	mov	%r13, 48(%rdi)			/* %r13 */
	mov	%r14, 56(%rdi)			/* %r14 */
	mov	%r15, 64(%rdi)			/* %r15 */

	/* the signal mask is not saved yet */
	movq	$0x0, 72(%rdi)			/* env[9] = 0 */

	/* res = sigprocmask(0, NULL, &env[10]) */
	push	%rdi
	mov	$0x0, %rdi
	mov	$0x0, %rsi
	lea	80(%rax), %rdx
#ifdef __PIC__
	call	sigprocmask@PLT
#else
	call	sigprocmask
#endif
	pop	%rdi

	/* the signal mask was saved */
	test	%eax, %eax			/* if(res == 0) */
	jnz	_setjmp_return
	movq	$0x1, 72(%rdi)			/*   env[9] = 1 */

_setjmp_return:
	mov	$0x0, %eax			/* return 0 */
	ret


/* sigaction */
.global __sigaction_sigtramp
.type __sigaction_sigtramp,@function
__sigaction_sigtramp:
	mov	%r15, %rdi
	mov	$SYS_setcontext, %rax
	syscall
	/* this should never be reached */
	mov	$SYS_exit, %rax
	mov	$-1, %rdi
	syscall

.global sigaction
.type sigaction,@function
sigaction:
	mov	$SYS_sigaction, %rax
#ifdef __PIC__
	lea	__sigaction_sigtramp@GOTPCREL(%rip), %rcx
	mov	(%rcx), %rcx
#else
	lea	__sigaction_sigtramp, %rcx
#endif
	mov	$0x2, %r8
#ifdef __PIC__
	jmp	_syscall@PLT
#else
	jmp	_syscall
#endif
#undef SYS_sigaction


/* sigsetjmp */
.global sigsetjmp
.type sigsetjmp,@function
sigsetjmp:
	test	%esi, %esi			/* if(savemask != 0) */
#ifdef __PIC__
	jnz	setjmp@PLT			/*   return setjmp() */
#else
	jnz	setjmp
#endif
#ifdef __PIC__
	jmp	_setjmp@PLT			/* return _setjmp() */
#else
	jmp	_setjmp
#endif
