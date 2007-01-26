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
	mov	SYS_ ## name, %g1; \
	jmp	_syscall


/* functions */
/* _exit */
.global _exit
_exit:
	mov	SYS_exit, %g1
	jmp	_syscall
