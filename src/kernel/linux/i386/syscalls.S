/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



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

/* mount */
.global mount
.type mount,@function
mount:
	mov	0x04(%esp), %eax
	mov	0x0c(%esp), %ecx
	mov	0x10(%esp), %edx
	mov	%eax, 0x0c(%esp)
	mov	%ecx, 0x10(%esp)
	mov	%edx, 0x04(%esp)
	mov	$0, %eax
	mov	%eax, 0x14(%esp)
	mov	$SYS_mount, %eax
	cmp	$0, %edx
	je	_syscall
	mov	(%edx), %edx
	mov	%edx, 0x04(%esp)
	jmp	_syscall
#undef SYS_mount


/* setjmp */
.global setjmp
.type setjmp,@function
setjmp:
	/* XXX from dietlibc */
	mov	0x00(%esp), %ecx
	lea	0x04(%esp), %edx
	mov	(%edx), %eax
	pushl	$0x00
	push	%eax
	call	_sigsetjmp_do
	add	$0x08, %esp
	ret


/* sigsetjmp */
.global sigsetjmp
.type sigsetjmp,@function
sigsetjmp:
	/* XXX from dietlibc */
	mov	0x00(%esp), %ecx
	lea	0x04(%esp), %edx
	mov	(%edx), %eax
_sigsetjmp_do:
	mov	%ebx, (0x00)(%eax)
	mov	%esi, (0x04)(%eax)
	mov	%edi, (0x08)(%eax)
	mov	%ebp, (0x0c)(%eax)
	mov	%edx, (0x10)(%eax)
	mov	%ecx, (0x14)(%eax)
	jmp	_sigjmp_save
