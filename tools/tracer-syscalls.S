/* $Id$ */
/* Copyright (c) 2012 Pierre Pronchery <khorben@defora.org> */
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



.text


/* NetBSD */
#if defined(__NetBSD__)
# if defined(__amd64__)
__syscall:
	push	%rdi
	push	%rsi
	push	%rax
	push	%rcx
	push	%rdx
	push	%r8
	push	%r9
	push	%r10
	push	%r11
	mov	%rdx, %rcx
	mov	%rsi, %rdx
	mov	%rdi, %rsi
	mov	%rax, %rdi
	call	analyze@PLT
	pop	%r11
	pop	%r10
	pop	%r9
	pop	%r8
	pop	%rdx
	pop	%rcx
	pop	%rax
	pop	%rsi
	pop	%rdi
	jmp	_syscall@PLT

#define SYSCALL(name) \
.global name; \
.type name,@function; \
name:; \
	mov	$SYS_ ## name, %rax; \
	jmp	__syscall@PLT
# else
#  warning Unsupported NetBSD architecture
# endif
#else
# warning Unsupported platform
#endif

#include "../src/syscalls.S"


/* platform-specific fixes */
/* NetBSD */
#if defined(__NetBSD__)
# if defined(__amd64__)
/* fstat */
.global __fstat50
.type __fstat50,@function
__fstat50:
	mov	$SYS_fstat, %rax
	jmp	__syscall@PLT

/* lstat */
.global __lstat50
.type __lstat50,@function
__lstat50:
	mov	$SYS_lstat, %rax
	jmp	__syscall@PLT

/* stat */
.global __stat50
.type __stat50,@function
__stat50:
	mov	$SYS_stat, %rax
	jmp	__syscall@PLT
# endif
#endif
