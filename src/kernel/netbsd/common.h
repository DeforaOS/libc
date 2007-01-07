/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef KERNEL_NETBSD_COMMON_H
# define KERNEL_NETBSD_COMMON_H

/* settings */
# define NETBSD_USE_LINUX_EMULATION


/* linux emulation */
# ifdef NETBSD_USE_LINUX_EMULATION
#  define SYS_exit		1
#  define SYS_fork	  	2
#  define SYS_read	  	3
#  define SYS_write	  	4
#  define SYS_open	  	5
#  define SYS_close	  	6
#  define SYS_waitpid	  	7
#  define SYS_link	  	9
#  define SYS_unlink		10
#  define SYS_execve		11
#  define SYS_chdir		12
#  define SYS_chmod		15
#  define SYS_getpid		20
#  define SYS_access		33
#  define SYS_sync		36
#  define SYS_kill		37
#  define SYS_mkdir		39
#  define SYS_rmdir		40
#  define SYS_dup		41
#  define SYS_pipe		42
#  define SYS_setpgid		57
#  define SYS_umask		60
#  define SYS_dup2		63
#  define SYS_getppid		64
#  define SYS_setsid		66
#  define SYS_gettimeofday	78
#  define SYS_symlink		83
#  define SYS_readlink		85
#  define SYS_readdir		89
#  define SYS_mmap		90
#  define SYS_munmap		91
#  define SYS_statvfs		99	/* FIXME is really statfs */
#  define SYS_stat		106
#  define SYS_lstat		107
#  define SYS_fstat		108
#  define SYS_wait4		114
#  define SYS_nanosleep		162
#  define SYS_vfork		190
#  define SYS_lchown		198
#  define SYS_getuid		199
#  define SYS_getgid		200
#  define SYS_geteuid		201
#  define SYS_getegid		202
#  define SYS_setreuid		203
#  define SYS_setregid		204
#  define SYS_chown		212
#  define SYS_setuid		213
#  define SYS_setgid		214
# endif /* NETBSD_USE_LINUX_EMULATION */

#endif /* !KERNEL_NETBSD_COMMON_H */
