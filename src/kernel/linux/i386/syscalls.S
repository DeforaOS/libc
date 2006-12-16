/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



_syscall0:
	mov	0x04(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall1:
	mov	0x08(%esp), %ebx
	mov	0x04(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall2:
	mov	0x0c(%esp), %ecx
	mov	0x08(%esp), %ebx
	mov	0x04(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall3:
	mov	0x10(%esp), %edx
	mov	0x0c(%esp), %ecx
	mov	0x08(%esp), %ebx
	mov	0x04(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall4:
	mov	0x14(%esp), %esi
	mov	0x10(%esp), %edx
	mov	0x0c(%esp), %ecx
	mov	0x80(%esp), %ebx
	mov	0x04(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall5:
	mov	0x18(%esp), %edi
	mov	0x14(%esp), %esi
	mov	0x10(%esp), %edx
	mov	0x0c(%esp), %ecx
	mov	0x08(%esp), %ebx
	mov	0x04(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall6:
	mov	0x04(%esp), %eax
	mov	%esp, %ebx
	add	$0x08, %ebx
	int	$0x80
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
