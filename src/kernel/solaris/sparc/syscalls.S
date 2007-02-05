/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



_syscall:
	ta	8
	/* FIXME handle errno */
	retl
	nop


/* macros */
#define SYSCALL(name) \
.global name; \
name:; \
	b	_syscall; \
	mov	SYS_ ## name, %g1


/* functions */
/* _exit */
.global _exit
_exit:
	b	_syscall
	mov	SYS_exit, %g1
