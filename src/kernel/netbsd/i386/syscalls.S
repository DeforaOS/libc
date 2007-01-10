/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



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
