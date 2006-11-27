/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef ___SYSCALLS_H
# define ___SYSCALLS_H

# if defined(__linux__)
/* Linux syscalls */
#  include "/usr/include/asm/unistd.h"
#  undef _syscall0
#  undef _syscall1
#  undef _syscall2
#  undef _syscall3
#  undef _syscall4
#  undef _syscall5
#  undef _syscall6
#  define SYS_exit	__NR_exit
#  define SYS_fork	__NR_fork
#  define SYS_read	__NR_read
#  define SYS_write	__NR_write
#  define SYS_open	__NR_open
#  define SYS_close	__NR_close
#  define SYS_waitpid	__NR_waitpid
#  define SYS_link	__NR_link
#  define SYS_unlink	__NR_unlink
#  define SYS_execve	__NR_execve
#  define SYS_chdir	__NR_chdir
#  define SYS_time	__NR_time
#  define SYS_mknod	__NR_mknod
#  define SYS_chmod	__NR_chmod
#  define SYS_lchown	__NR_lchown
#  define SYS_getpid	__NR_getpid
#  define SYS_mount	__NR_mount
#  define SYS_umount	__NR_umount
#  define SYS_setuid	__NR_setuid
#  define SYS_getuid	__NR_getuid
#  define SYS_ptrace	__NR_ptrace
#  define SYS_alarm	__NR_alarm
#  define SYS_utime	__NR_utime
#  define SYS_access	__NR_access
#  define SYS_nice	__NR_nice
#  define SYS_sync	__NR_sync
#  define SYS_kill	__NR_kill
#  define SYS_mkdir	__NR_mkdir
#  define SYS_rmdir	__NR_rmdir
#  define SYS_dup	__NR_dup
#  define SYS_pipe	__NR_pipe
#  define SYS_times	__NR_times
#  define SYS_brk	__NR_brk
#  define SYS_setgid	__NR_setgid
#  define SYS_getgid	__NR_getgid
#  define SYS_signal	__NR_signal
#  define SYS_geteuid	__NR_geteuid
#  define SYS_getegid	__NR_getegid
#  define SYS_setpgid	__NR_setpgid
#  define SYS_umask	__NR_umask
#  define SYS_dup2	__NR_dup2
#  define SYS_getppid	__NR_getppid
#  define SYS_setsid	__NR_setsid
#  define SYS_setreuid	__NR_setreuid
#  define SYS_setregid	__NR_setregid
#  define SYS_symlink	__NR_symlink
#  define SYS_readlink	__NR_readlink
#  define SYS_mmap	__NR_mmap
#  define SYS_munmap	__NR_munmap
#  define SYS_statfs	__NR_statfs
#  define SYS_fstatfs	__NR_fstatfs
#  define SYS_stat	__NR_stat
#  define SYS_lstat	__NR_lstat
#  define SYS_fstat	__NR_fstat
#  define SYS_uname	__NR_uname
#  define SYS_chown	__NR_chown
#  define SYS_getcwd	__NR_getcwd
#  define SYS_vfork	__NR_vfork
# elif defined(__NetBSD__)
/* NetBSD syscalls */
#  include "/usr/include/sys/syscall.h"
#  define SYS_stat	SYS___stat13
#  define SYS_lstat	SYS___lstat13
#  define SYS_fstat	SYS___fstat13
#  define SYS_statvfs	SYS_statvfs1
# elif defined(__sun__)
/* Solaris syscalls */
#  include "/usr/include/sys/syscall.h"
# else
#  error Unsupported platform
# endif


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
# define syscall6(type, name, type1, arg1, type2, arg2, type3, arg3, \
		type4, arg4, type5, arg5, type6, arg6) \
	type name(type1 arg1, type2 arg2, type3 arg3, type4 arg4, type5 arg5, \
			type6 arg6) \
	{ return (type) _syscall6(SYS_ ## name, (int)arg1, (int)arg2, \
			(int)arg3, (int)arg4, (int)arg5, (int)arg6); }

extern int _syscall0(int name);
extern int _syscall1(int name, int arg1);
extern int _syscall2(int name, int arg1, int arg2);
extern int _syscall3(int name, int arg1, int arg2, int arg3);
extern int _syscall4(int name, int arg1, int arg2, int arg3, int arg4);
extern int _syscall6(int name, int arg1, int arg2, int arg3, int arg4, int arg5,
		int arg6);

#endif /* !___SYSCALLS_H */
