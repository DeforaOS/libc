/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



_syscall6:
	/* FIXME use the stack? */
_syscall5:
	mov	%i5, %o4
_syscall4:
	mov	%i4, %o3
_syscall3:
	mov	%i3, %o2
_syscall2:
	mov	%i2, %o1
_syscall1:
	mov	%i1, %o0
_syscall0:
	mov	%i0, %g1	/* syscall number */
	ta	$0x8
	/* FIXME errno */
	ret
