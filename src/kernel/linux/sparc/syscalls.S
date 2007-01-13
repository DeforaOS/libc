/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



_syscall0:
	jmp	trap
	nop

_syscall1:
	mov	%i1, %o0
	jmp	trap
	nop

_syscall2:
	mov	%i2, %o1
	jmp	trap
	nop

_syscall3:
	mov	%i3, %o2
	jmp	trap
	nop

_syscall4:
	mov	%i4, %o3
	jmp	trap
	nop

_syscall5:
	mov	%i5, %o4
	jmp	trap
	nop

_syscall6:
	/* FIXME how to get the last arg? */

.trap:
	mov	%i0, %g1	/* syscall number */
	ta	8
	/* FIXME errno */
	ret
	nop
