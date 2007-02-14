/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



_syscall:
	ta	0
	bcc	.errnoret
	nop
	set	errno, %g1
	st	%o0, [%g1]
	set	-1, %o0
.errnoret:
	retl
	nop


/* macros */
#define SYSCALL(name) \
.global name; \
name:; \
	b	_syscall; \
	mov	SYS_ ## name, %g1


/* functions */
/* _brk */
.global _brk
_brk:
	b	_syscall
	mov	SYS_brk, %g1
#undef SYS_brk

/* _exit */
.global _exit
_exit:
	b	_syscall
	mov	SYS_exit, %g1
