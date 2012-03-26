/* $Id$ */
/* Copyright (c) 2006-2012 Pierre Pronchery <khorben@defora.org> */
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
/* FIXME:
 * - check errors from sigprocmask()?
 * - some syscalls may return an additional value into %edx (eg lseek)
 * - ftruncate() and truncate() probably need a wrapper (for padding) */



_syscall:
	int	$0x80
	jnc	_syscall_return
.errno:
	mov	%eax, errno
	mov	$-1, %eax
_syscall_return:
	ret


/* macros */
#define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %eax; \
	jmp	_syscall


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
	/* edx = env */
	mov	8(%ebp), %edx
	/* restore registers */
	mov	0(%edx), %ecx			/* return address */
	mov	%ecx, 4(%ebp)
	mov	4(%edx), %ebx
	mov	8(%edx), %esp			/* stack pointer */
	mov	12(%edx), %ecx
	mov	%ecx, 0(%ebp)			/* base pointer */
	mov	16(%edx), %esi
	mov	20(%edx), %edi
	/* eax = val */
	mov	12(%ebp), %eax
	/* if(val == 0) val = 1 */
	test	%eax, %eax
	jnz	__longjmp_return
	inc	%eax
__longjmp_return:
	/* return val */
	pop	%ebp
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
	/* eax = env */
	mov	8(%ebp), %eax
	/* ecx = env[6] */
	mov	24(%eax), %ecx
	test	%ecx, %ecx
	jz	_longjmp_registers

	/* restore the signal mask */
	/* sigprocmask(SIG_SETMASK, &env[7], NULL) */
	push	$0x0
	lea	28(%eax), %ecx
	push	%ecx
	push	$0x3
	call	sigprocmask
	add	$12, %esp
	/* eax = env */
	mov	8(%ebp), %eax

	/* restore registers */
_longjmp_registers:
	mov	0(%eax), %ecx			/* return address */
	mov	%ecx, 4(%ebp)
	mov	4(%eax), %ebx
	mov	8(%eax), %esp			/* stack pointer */
	mov	12(%eax), %ecx
	mov	%ecx, 0(%ebp)			/* base pointer */
	mov	16(%eax), %esi
	mov	20(%eax), %edi

	/* if(val != 0) goto _longjmp_return; else val++ */
	/* eax = val */
	mov	12(%ebp), %eax
	test	%eax, %eax
	jnz	_longjmp_return
	inc	%eax

	/* return val */
_longjmp_return:
	pop	%ebp
	ret


/* pipe */
.global pipe
.type pipe,@function
pipe:
	mov	$SYS_pipe, %eax
	int	$0x80
	jc	.errno
	mov	4(%esp), %ecx
	mov	%eax, (%ecx)
	mov	%edx, 4(%ecx)
	mov	$0, %eax
	ret
#undef SYS_pipe


/* _setjmp */
.global _setjmp
.type _setjmp,@function
_setjmp:
	push	%ebp
	mov	%esp, %ebp
	/* eax = env */
	mov	8(%ebp), %eax
	/* save registers */
	mov	4(%ebp), %edx			/* return address */
	mov	%edx, 0(%eax)
	mov	%ebx, 4(%eax)
	mov	%ebp, 8(%eax)			/* stack pointer */
	mov	0(%esp), %edx			/* base pointer */
	mov	%edx, 12(%eax)
	mov	%esi, 16(%eax)
	mov	%edi, 20(%eax)
	/* the signal mask is not saved */
	lea	24(%eax), %edx
	movl	$0x0, (%edx)
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
	mov	4(%ebp), %ecx			/* return address */
	mov	%ecx, 0(%eax)
	mov	%ebx, 4(%eax)
	mov	%ebp, 8(%eax)			/* stack pointer */
	mov	0(%ebp), %ecx			/* base pointer */
	mov	%ecx, 12(%eax)
	mov	%esi, 16(%eax)
	mov	%edi, 20(%eax)

	/* the signal mask is not saved yet */
	/* env[6] = 0 */
	lea	24(%eax), %ecx
	movl	$0x0, (%ecx)

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
	lea	24(%eax), %ecx
	movl	$0x1, (%ecx)

	/* return 0 */
_setjmp_return:
	mov	$0x0, %eax
	pop	%ebp
	ret


/* sigaction */
.global __sigaction_sigtramp
.type __sigaction_sigtramp,@function
__sigaction_sigtramp:
	lea	12+128(%esp), %eax
	mov	%eax, 4(%esp)
	mov	$SYS_setcontext, %eax
	int	$0x80
	/* should not happen */
	movl	$-1, 4(%esp)
	int	$0x80

.global sigaction
.type sigaction,@function
sigaction:
	lea	__sigaction_sigtramp, %eax
	mov	%eax, 16(%esp)
	mov	$SYS_sigaction, %eax
	movl	$0x2, 20(%esp)
	jmp	_syscall
#undef SYS_sigaction


/* sigsetjmp */
.global sigsetjmp
.type sigsetjmp,@function
sigsetjmp:
	/* if(savemask == 0) return _setjmp() */
	mov	8(%esp), %eax
	test	%eax, %eax
	jnz	_sigsetjmp_save
	jmp	_setjmp
_sigsetjmp_save:
	/* else return setjmp() */
	jmp	setjmp
