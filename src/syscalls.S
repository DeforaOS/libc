/* syscalls.S */



.text
.global _syscall0, _syscall1, _syscall2, _syscall3, _syscall4, _syscall5
_syscall0:
	mov	0x4(%esp), %eax
	int	$0x80
	ret

_syscall1:
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	ret

_syscall2:
	mov	0x12(%esp), %ecx
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	ret

_syscall3:
	mov	0x16(%esp), %edx
	mov	0x12(%esp), %ecx
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	ret

_syscall4:
	mov	0x20(%esp), %esi
	mov	0x16(%esp), %edx
	mov	0x12(%esp), %ecx
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	ret

_syscall5:
	mov	0x24(%esp), %edi
	mov	0x20(%esp), %esi
	mov	0x16(%esp), %edx
	mov	0x12(%esp), %ecx
	mov	0x8(%esp), %ebx
	mov	0x4(%esp), %eax
	int	$0x80
	ret
