/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "common.h"


.text
.global _syscall0, _syscall1, _syscall2, _syscall3, _syscall4, _syscall5, \
		_syscall6


/* syscalls */
#if defined(__linux__)
# if defined(__i386__)
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
	push	%ebp
	mov	0x20(%esp), %ebp
	mov	0x1c(%esp), %edi
	mov	0x18(%esp), %esi
	mov	0x14(%esp), %edx
	mov	0x10(%esp), %ecx
	mov	0x0c(%esp), %ebx
	mov	0x08(%esp), %eax
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
# else /* !__i386__ */
#  warning Unsupported Linux architecture
# endif
#elif defined(__NetBSD__)
# if defined(__i386__)
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
# else /* !__i386__ */
#  warning Unsupported NetBSD architecture
# endif
#else
# warning Unsupported Operating System and architecture
#endif
