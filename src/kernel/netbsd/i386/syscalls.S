/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#if defined(NETBSD_USE_LINUX_EMULATION)
_syscall0:
	mov	0x04(%esp), %eax
	int	$0x80
	jmp	.errno

_syscall1:
	mov	0x04(%esp), %eax
	push	%ebx
	mov	0x0c(%esp), %ebx
	int	$0x80
	pop	%ebx
	jmp	.errno

_syscall2:
	mov	0x04(%esp), %eax
	push	%ebx
	push	%ecx
	mov	0x14(%esp), %ecx
	mov	0x10(%esp), %ebx
	int	$0x80
	pop	%ecx
	pop	%ebx
	jmp	.errno

_syscall3:
	mov	0x04(%esp), %eax
	push	%ebx
	push	%ecx
	push	%edx
	mov	0x1c(%esp), %edx
	mov	0x18(%esp), %ecx
	mov	0x14(%esp), %ebx
	int	$0x80
	pop	%edx
	pop	%ecx
	pop	%ebx
	jmp	.errno

_syscall4:
	mov	0x04(%esp), %eax
	push	%ebx
	push	%ecx
	push	%edx
	push	%esi
	mov	0x24(%esp), %esi
	mov	0x20(%esp), %edx
	mov	0x1c(%esp), %ecx
	mov	0x18(%esp), %ebx
	int	$0x80
	pop	%esi
	pop	%edx
	pop	%ecx
	pop	%ebx
	jmp	.errno

_syscall5:
	mov	0x04(%esp), %eax
	push	%ebx
	push	%ecx
	push	%edx
	push	%esi
	push	%edi
	mov	0x2c(%esp), %edi
	mov	0x28(%esp), %esi
	mov	0x24(%esp), %edx
	mov	0x20(%esp), %ecx
	mov	0x1c(%esp), %ebx
	int	$0x80
	pop	%edi
	pop	%esi
	pop	%edx
	pop	%ecx
	pop	%ebx
	jmp	.errno

_syscall6:
	mov	0x04(%esp), %eax
	push	%ebx
	push	%ecx
	push	%edx
	push	%esi
	push	%edi
	push	%ebp
	mov	0x34(%esp), %ebp
	mov	0x30(%esp), %edi
	mov	0x2c(%esp), %esi
	mov	0x28(%esp), %edx
	mov	0x24(%esp), %ecx
	mov	0x20(%esp), %ebx
	int	$0x80
	pop	%ebp
	pop	%edi
	pop	%esi
	pop	%edx
	pop	%ecx
	pop	%ebx
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
#else /* !NETBSD_USE_LINUX_EMULATION */
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
#endif
