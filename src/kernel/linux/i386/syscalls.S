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



_syscall:
	push	%ebx
	push	%esi
	push	%edi
	mov	0x10(%esp), %ebx
	mov	0x14(%esp), %ecx
	mov	0x18(%esp), %edx
	mov	0x1c(%esp), %esi
	mov	0x20(%esp), %edi
	int	$0x80
	pop	%edi
	pop	%esi
	pop	%ebx
.errno:
	cmp	$0, %eax
	jge	.errnoret
	neg	%eax
	mov	%eax, errno
	mov	$-1, %eax
.errnoret:
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
	jmp	_syscall
#undef SYS_brk


/* _exit */
.global _exit
.type _exit,@function
_exit:
	mov	$SYS_exit, %eax
	jmp	_syscall


/* _ipc */
SYSCALL(_ipc)


/* longjmp */
.global longjmp
.type longjmp,@function
longjmp:
	push	%ebp
	mov	%esp, %ebp
	/* edx = env */
	mov	8(%ebp), %edx
	/* eax = val */
	mov	12(%ebp), %eax
	/* restore registers */
	mov	0(%edx), %ecx			/* return address */
	mov	%ecx, 4(%ebp)
	mov	4(%edx), %ebx
	mov	8(%edx), %esp			/* stack pointer */
	mov	12(%edx), %ecx
	mov	%ecx, 0(%ebp)			/* base pointer */
	mov	16(%edx), %esi
	mov	20(%edx), %edi
	/* if(val == 0) val = 1 */
	test	%eax, %eax
	jnz	_longjmp_return
	inc	%eax
_longjmp_return:
	/* return val */
	pop	%ebp
	ret


/* mmap */
.global mmap
.type mmap,@function
mmap:
	mov	$SYS_mmap, %eax
	push	%ebx
	mov	%esp, %ebx
	add	$0x08, %ebx
	int	$0x80
	pop	%ebx
	cmp	$-255, %eax
	jl	.errnoret
	jmp	.errno
#undef SYS_mmap


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
	mov	0(%esp), %edx			/* base pointer */
	mov	%edx, 12(%eax)
	mov	%esi, 16(%eax)
	mov	%edi, 20(%eax)
	/* return 0 */
	mov	$0x0, %eax
	pop	%ebp
	ret
