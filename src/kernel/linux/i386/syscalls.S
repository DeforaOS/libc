/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



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
name:; \
	mov	$SYS_ ## name, %eax; \
	jmp	_syscall


/* functions */
/* _brk */
.global _brk
_brk:
	mov	$SYS_brk, %eax
	jmp	_syscall
#undef SYS_brk

/* _exit */
.global _exit
_exit:
	mov	$SYS_exit, %eax
	jmp	_syscall

/* mmap */
.global mmap
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
