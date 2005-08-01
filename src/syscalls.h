/* syscalls.h */



#ifndef ___SYSCALLS_H
# define ___SYSCALLS_H


/* linux syscalls */
# define SYS_exit	1
# define SYS_fork	2
# define SYS_read	3
# define SYS_write	4
# define SYS_open	5
# define SYS_close	6
# define SYS_waitpid	7
# define SYS_link	9
# define SYS_unlink	10
# define SYS_execve	11
# define SYS_chdir	12
# define SYS_time	13
# define SYS_mknod	14
# define SYS_chmod	15
# define SYS_lchown	16
# define SYS_getpid	20
# define SYS_mount	21
# define SYS_umount	22
# define SYS_setuid	23
# define SYS_getuid	24
# define SYS_ptrace	26
# define SYS_alarm	27
# define SYS_utime	30
# define SYS_access	33
# define SYS_nice	34
# define SYS_sync	36
# define SYS_kill	37
# define SYS_mkdir	39
# define SYS_rmdir	40
# define SYS_dup	41
# define SYS_pipe	42
# define SYS_times	43
# define SYS_brk	45
# define SYS_setgid	46
# define SYS_getgid	47
# define SYS_signal	48
# define SYS_geteuid	49
# define SYS_getegid	50
# define SYS_setpgid	57
# define SYS_dup2	63
# define SYS_getppid	64
# define SYS_setsid	66
# define SYS_setreuid	70
# define SYS_setregid	71
# define SYS_symlink	83
# define SYS_readlink	85
# define SYS_mmap	90
# define SYS_munmap	91
# define SYS_stat	106
# define SYS_lstat	107
# define SYS_fstat	108
# define SYS_uname	122
# define SYS_chown	182
# define SYS_getcwd	183
# define SYS_vfork	190
# define SYS_waitid	284


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
