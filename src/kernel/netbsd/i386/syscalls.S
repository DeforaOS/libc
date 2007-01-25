/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



_syscall:
	int	$0x80
.errno:
	cmp	$0, %eax
	jge	.errnoret
	neg	%eax
	mov	%eax, errno
	mov	$-1, %eax
.errnoret:
	ret


/* macros */
#define SYSCALL(name) \
.global name; \
name:; \
	mov	$SYS_ ## name, %eax; \
	jmp	_syscall


/* functions */
/* _exit */
.global _exit
_exit:
	mov	$SYS_exit, %eax
	jmp	_syscall
