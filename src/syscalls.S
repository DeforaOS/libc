/* syscalls.S */



.text
.global _syscall0, _syscall1, _syscall2, _syscall3
_syscall0:
	push	%ebp
	mov	0x4(%esp), %eax
	int	$0x80
	pop	%ebp
	ret

_syscall1:
	push	%ebp
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	pop	%ebp
	ret

_syscall2:
	push	%ebp
	mov	0x12(%esp), %ecx
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	pop	%ebp
	ret

_syscall3:
	push	%ebp
	mov	0x16(%esp), %edx
	mov	0x12(%esp), %ecx
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	pop	%ebp
	ret
