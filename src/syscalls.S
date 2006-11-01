/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



.text
.global _syscall0, _syscall1, _syscall2, _syscall3, _syscall4, _syscall5, \
		_syscall6
#if defined(__linux__)
_syscall0:
	mov	0x4(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall1:
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall2:
	mov	0x12(%esp), %ecx
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall3:
	mov	0x16(%esp), %edx
	mov	0x12(%esp), %ecx
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall4:
	mov	0x20(%esp), %esi
	mov	0x16(%esp), %edx
	mov	0x12(%esp), %ecx
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall5:
	mov	0x24(%esp), %edi
	mov	0x20(%esp), %esi
	mov	0x16(%esp), %edx
	mov	0x12(%esp), %ecx
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall6:
	push	%ebp
	mov	0x32(%esp), %ebp
	mov	0x28(%esp), %edi
	mov	0x24(%esp), %esi
	mov	0x20(%esp), %edx
	mov	0x16(%esp), %ecx
	mov	0x12(%esp), %ebx
	mov	0x8(%esp), %eax
	int	$0x80
	pop	%ebp
	jmp	.errno

.global errno
.errno:
	cmp	$0, %eax
	jge	.errnoret
	neg	%eax
	mov	%eax, errno
	mov	$-1, %eax
.errnoret:
	ret
#elif defined(__NetBSD__)
_syscall0:
_syscall1:
_syscall2:
_syscall3:
_syscall4:
_syscall5:
_syscall6:
	pop	%ecx
	pop	%eax
	push	%ecx
	int	$0x80
	push	%ecx
	ret
#else
# error Unsupported system
#endif
