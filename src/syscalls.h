/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef SYSCALLS_H
# define SYSCALLS_H

# if defined(__linux__)
#  include "kernel/linux/common.h"
# elif defined(__NetBSD__)
#  include "kernel/netbsd/common.h"
# elif defined(__sun__)
#  include "kernel/solaris/common.h"
# else
#  error Unsupported platform
# endif


/* macros */
# define syscall0(type, name) \
	type name(void) { return (type) _syscall0(SYS_ ## name); }
# define syscall1(type, name, type1, arg1) \
	type name(type1 arg1) { return (type) _syscall1(SYS_ ## name, \
			(int)arg1); }
# define syscall2(type, name, type1, arg1, type2, arg2) \
	type name(type1 arg1, type2 arg2) \
	{ return (type) _syscall2(SYS_ ## name, (int)arg1, (int)arg2); }
# define syscall3(type, name, type1, arg1, type2, arg2, type3, arg3) \
	type name(type1 arg1, type2 arg2, type3 arg3) \
	{ return (type) _syscall3(SYS_ ## name, (int)arg1, (int)arg2, \
			(int)arg3); }
# define syscall4(type, name, type1, arg1, type2, arg2, type3, arg3, \
		type4, arg4) \
	type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4) \
	{ return (type) _syscall4(SYS_ ## name, (int)arg1, (int)arg2, \
			(int)arg3, (int)arg4); }
# define syscall5(type, name, type1, arg1, type2, arg2, type3, arg3, \
		type4, arg4, type5, arg5) \
	type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5) \
	{ return (type) _syscall5(SYS_ ## name, (int)arg1, (int)arg2, \
			(int)arg3, (int)arg4, (int)arg5); }
# define syscall6(type, name, type1, arg1, type2, arg2, type3, arg3, \
		type4, arg4, type5, arg5, type6, arg6) \
	type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, \
			type6 arg6) \
	{ return (type) _syscall6(SYS_ ## name, (int)arg1, (int)arg2, \
			(int)arg3, (int)arg4, (int)arg5, (int)arg6); }


/* functions */
extern int _syscall0(int name);
extern int _syscall1(int name, int arg1);
extern int _syscall2(int name, int arg1, int arg2);
extern int _syscall3(int name, int arg1, int arg2, int arg3);
extern int _syscall4(int name, int arg1, int arg2, int arg3, int arg4);
extern int _syscall5(int name, int arg1, int arg2, int arg3, int arg4,
		int arg5);
extern int _syscall6(int name, int arg1, int arg2, int arg3, int arg4, int arg5,
		int arg6);

#endif /* !SYSCALLS_H */
