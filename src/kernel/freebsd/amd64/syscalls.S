/* $Id$ */
/* Copyright (c) 2009-2012 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



_syscall:
	mov	%rcx, %r10
	syscall
	jnc	.errnoret
.errno:
#ifdef PIC
	mov	%rax, errno@GOTPCREL(%rip)
#else
	mov	%rax, errno
#endif
	mov	$-1, %rax
.errnoret:
	ret


/* macros */
#define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %rax; \
	jmp	_syscall


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
	jmp	_syscall


/* execve */
.global execve
.type execve,@function
execve:
	mov	$SYS_execve, %rax
	syscall
#ifdef PIC
	mov	%rax, errno@GOT(%rip)
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
	mov	0(%rdi), %rdx			/* return address */
	mov	%rdx, 0(%rsp)
	mov	8(%rdi), %rbx
	mov	16(%rdi), %rsp			/* stack pointer */
	mov	24(%rdi), %rbp			/* base pointer */
	mov	32(%rdi), %r11			/* %r11 */
	mov	40(%rdi), %r12			/* %r12 */
	mov	48(%rdi), %r13			/* %r13 */
	mov	56(%rdi), %r14			/* %r14 */
	mov	64(%rdi), %r15			/* %r15 */

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
	lea	72(%rdi), %rdx
	mov	(%rdx), %rdx
	test	%rdx, %rdx
	jz	_longjmp_registers

	/* restore the signal mask */
	/* sigprocmask(SIG_SETMASK, &env[10], NULL) */
	push	%rdi
	push	%rsi
	mov	$0x3, %rdi
	mov	$0x0, %rsi
	lea	80(%rdi), %rdx
#ifdef PIC
	call	sigprocmask@PLT
#else
	call	sigprocmask
#endif
	pop	%rsi
	pop	%rdi

	/* restore registers */
_longjmp_registers:
	mov	0(%rdi), %rdx			/* return address */
	mov	%rdx, 0(%rsp)
	mov	8(%rdi), %rbx
	mov	16(%rdi), %rsp			/* stack pointer */
	mov	24(%rdi), %rbp			/* base pointer */
	mov	32(%rdi), %r11			/* %r11 */
	mov	40(%rdi), %r12			/* %r12 */
	mov	48(%rdi), %r13			/* %r13 */
	mov	56(%rdi), %r14			/* %r14 */
	mov	64(%rdi), %r15			/* %r15 */

	/* if(val != 0) goto _longjmp_return; else val++ */
	mov	%esi, %eax
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
