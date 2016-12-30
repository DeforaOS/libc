/* $Id$ */
/* Copyright (c) 2008-2012 Pierre Pronchery <khorben@defora.org> */
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
/* FIXME:
 * - directly taken from the one for NetBSD */



_syscall:
	int	$0x80
	jnc	_syscall_return
.errno:
	mov	%eax, errno
	mov	$-1, %eax
_syscall_return:
	ret


/* macros */
#ifndef SYSCALL
# define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %eax; \
	jmp	_syscall
#endif


/* functions */
/* _brk */
.global _brk
.type _brk,@function
_brk:
	mov	$SYS_brk, %eax
	int	$0x80
	jc	.errno
	ret
#undef SYS_brk

/* _exit */
.global _exit
.type _exit,@function
_exit:
	mov	$SYS_exit, %eax
	jmp	_syscall

/* execve */
.global execve
.type execve,@function
execve:
	mov	$SYS_execve, %eax
	int	$0x80
	mov	%eax, errno
	mov	$-1, %eax
	ret
#undef SYS_execve


/* _longjmp */
.global _longjmp
.type _longjmp,@function
_longjmp:
	push	%ebp
	mov	%esp, %ebp

	mov	12(%ebp), %eax			/* eax = val */

	/* restore registers */
	mov	8(%ebp), %edx			/* edx = env */
	mov	20(%edx), %edi			/* edi = env[5] */
	mov	16(%edx), %esi			/* esi = env[4] */
	mov	12(%edx), %ecx			/* base pointer = env[3] */
	mov	%ecx, %ebp
	mov	8(%edx), %esp			/* stack pointer = env[2] */
	mov	4(%edx), %ebx			/* ebx = env[1] */
	mov	0(%edx), %ecx			/* return address = env[0] */
	mov	%ecx, 0(%esp)

	/* if(val != 0) return val; else return ++val */
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
	push	%ebp
	mov	%esp, %ebp

	/* if(env[6] == 0) goto _longjmp_registers */
	mov	8(%ebp), %eax			/* eax = env */
	mov	24(%eax), %ecx			/* ecx = env[6] */
	test	%ecx, %ecx
	jz	_longjmp_registers

	/* restore the signal mask */
	/* sigprocmask(SIG_SETMASK, &env[7], NULL) */
	push	$0x0
	lea	28(%eax), %ecx
	push	%ecx
	push	$0x2
	call	sigprocmask
	add	$12, %esp

	/* restore registers */
_longjmp_registers:
	mov	8(%ebp), %edx			/* edx = env */
	mov	12(%ebp), %eax			/* eax = val */
	mov	20(%edx), %edi			/* edi = env[5] */
	mov	16(%edx), %esi			/* esi = env[4] */
	mov	12(%edx), %ecx			/* base pointer = env[3] */
	mov	%ecx, %ebp
	mov	8(%edx), %esp			/* stack pointer = env[2] */
	mov	4(%edx), %ebx			/* ebx = env[1] */
	mov	0(%edx), %ecx			/* return address = env[0] */
	mov	%ecx, 0(%esp)

	/* if(val != 0) return val; else return ++val */
	test	%eax, %eax
	jnz	_longjmp_return
	inc	%eax

	/* return val */
_longjmp_return:
	ret


/* _setjmp */
.global _setjmp
.type _setjmp,@function
_setjmp:
	push	%ebp
	mov	%esp, %ebp

	/* save registers */
	mov	8(%ebp), %eax			/* eax = env */
	mov	4(%ebp), %edx			/* env[0] = return address */
	mov	%edx, 0(%eax)
	mov	%ebx, 4(%eax)			/* env[1] = ebx */
	mov	%ebp, 8(%eax)			/* env[2] = stack pointer */
	mov	0(%esp), %edx			/* env[3] = base pointer */
	mov	%edx, 12(%eax)
	mov	%esi, 16(%eax)			/* env[4] = esi */
	mov	%edi, 20(%eax)			/* env[5] = edi */

	/* the signal mask is not saved */
	movl	$0x0, 24(%eax)			/* env[6] = 0 */

	/* return 0 */
	mov	$0x0, %eax
	pop	%ebp
	ret


/* setjmp */
.global setjmp
.type setjmp,@function
setjmp:
	push	%ebp
	mov	%esp, %ebp

	/* eax = env */
	mov	8(%ebp), %eax

	/* save registers */
	mov	4(%ebp), %edx			/* return address */
	mov	%edx, 0(%eax)
	mov	%ebx, 4(%eax)
	mov	%ebp, 8(%eax)			/* stack pointer */
	mov	0(%ebp), %edx			/* base pointer */
	mov	%edx, 12(%eax)
	mov	%esi, 16(%eax)
	mov	%edi, 20(%eax)

	/* the signal mask is not saved yet */
	movl	$0x0, 24(%eax)			/* env[6] = 0 */

	/* res = sigprocmask(0, NULL, &env[7]) */
	lea	28(%eax), %ecx
	push	%ecx
	push	$0x0
	push	$0x0
	call	sigprocmask
	add	$12, %esp

	/* the signal mask was saved */
	/* if(res == 0) env[6] = 1 */
	test	%eax, %eax
	jnz	_setjmp_return
	mov	8(%ebp), %eax
	movl	$0x1, 24(%eax)

	/* return 0 */
_setjmp_return:
	mov	$0x0, %eax
	pop	%ebp
	ret


/* sigsetjmp */
.global sigsetjmp
.type sigsetjmp,@function
sigsetjmp:
	/* if(savemask != 0) return setjmp(); else return _setjmp() */
	mov	8(%esp), %eax
	test	%eax, %eax
	jnz	setjmp
	jmp	_setjmp
