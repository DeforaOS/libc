/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



_syscall:
	ta	0
	/* FIXME errno */
	ret
	nop


/* macros */
#define SYSCALL(name) \
.global name; \
name:; \
	jmp	_syscall; \
	mov	SYS_ ## name, %g1


/* functions */
/* _exit */
.global _exit
_exit:
	jmp	_syscall
	mov	SYS_exit, %g1
