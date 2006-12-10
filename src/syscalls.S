/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



.text
.global _syscall0, _syscall1, _syscall2, _syscall3, _syscall4, _syscall5, \
		_syscall6


/* Linux */
#if defined(__linux__)
# include "kernel/linux/common.h"
# if defined(__i386__)
#  include "kernel/linux/i386/syscalls.S"
# else
#  warning Unsupported Linux architecture
# endif

/* NetBSD */
#elif defined(__NetBSD__)
# include "kernel/netbsd/common.h"
# if defined(__i386__)
#  include "kernel/netbsd/i386/syscalls.S"
# else
#  warning Unsupported NetBSD architecture
# endif

/* Unknown */
#else
# warning Unsupported kernel and architecture
#endif
