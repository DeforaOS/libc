/* $Id$ */
/* Copyright (c) 2011-2018 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#ifndef KERNEL_LINUX_SYS_SYSCALL_H
# define KERNEL_LINUX_SYS_SYSCALL_H


/* architecture specific: amd64 */
# ifdef __amd64__
#  define SYS_read		0
#  define SYS_write		1
#  define SYS_open		2
#  define SYS_close		3
#  define SYS_stat		4
#  define SYS_fstat		5
#  define SYS_lstat		6
#  define SYS_poll		7
#  define SYS_lseek		8
#  define SYS_mmap		9
#  define SYS_mprotect		10
#  define SYS_munmap		11
#  define SYS_brk		12
#  define SYS_ioctl		16
#  define SYS_access		21
#  define SYS_pipe		22
#  define SYS_select		23
#  define SYS_mremap		25
#  define SYS_shmget		29
#  define SYS_shmat		30
#  define SYS_shmctl		31
#  define SYS_dup		32
#  define SYS_dup2		33
#  define SYS_nanosleep		35
#  define SYS_getitimer		36
#  define SYS_alarm		37
#  define SYS_setitimer		38
#  define SYS_getpid		39
#  define SYS_fork		57
#  define SYS_vfork		58
#  define SYS_execve		59
#  define SYS_exit		60
#  define SYS_wait4		61
#  define SYS_kill		62
#  define SYS_uname		63
#  define SYS_msgget		68
#  define SYS_msgsnd		69
#  define SYS_msgrcv		70
#  define SYS_msgctl		71
#  define SYS_fcntl		72
#  define SYS_flock		73
#  define SYS_fsync		74
#  define SYS_truncate		76
#  define SYS_ftruncate		77
#  define SYS_getdents		78
#  define SYS__getcwd		79
#  define SYS_chdir		80
#  define SYS_fchdir		81
#  define SYS_rename		82
#  define SYS_mkdir		83
#  define SYS_rmdir		84
#  define SYS_creat		85
#  define SYS_link		86
#  define SYS_unlink		87
#  define SYS_symlink		88
#  define SYS_readlink		89
#  define SYS_chmod		90
#  define SYS_fchmod		91
#  define SYS_chown		92
#  define SYS_fchown		93
#  define SYS_lchown		94
#  define SYS_umask		95
#  define SYS_gettimeofday	96
#  define SYS_getrlimit		97
#  define SYS_getrusage		98
#  define SYS_times		100
#  define SYS_ptrace		101
#  define SYS_getuid		102
#  define SYS_getgid		104
#  define SYS_setuid		105
#  define SYS_setgid		106
#  define SYS_geteuid		107
#  define SYS_getegid		108
#  define SYS_setpgid		109
#  define SYS_getppid		110
#  define SYS_getpgrp		111
#  define SYS_setsid		112
#  define SYS_setreuid		113
#  define SYS_setregid		114
#  define SYS_utime		132
#  define SYS_mknod		133
#  define SYS_statfs		137
#  define SYS_fstatfs		138
#  define SYS_getpriority	140
#  define SYS_setpriority	141
#  define SYS_mlock		149
#  define SYS_munlock		150
#  define SYS_prctl		157
#  define SYS_arch_prctl	158
#  define SYS_setrlimit		160
#  define SYS_chroot		161
#  define SYS_sync		162
#  define SYS__mount		165
#  define SYS_unmount		166
#  define SYS_reboot		169
#  define SYS_sethostname	170
#  define SYS_set_thread_area	205
#  define SYS_get_thread_area	211
#  define SYS_utimes		235
#  define SYS_openat		257
#  define SYS_mkdirat		258
#  define SYS_mknodat		259
#  define SYS_fchownat		260
#  define SYS_futimesat		261
#  define SYS_unlinkat		263
#  define SYS_renameat		264
#  define SYS_linkat		265
#  define SYS_symlinkat		266
#  define SYS_readlinkat	267
#  define SYS_fchmodat		268
#  define SYS_faccessat		269

/* generic */
# else
#  define SYS_exit		1
#  define SYS_fork		2
#  define SYS_read		3
#  define SYS_write		4
#  define SYS_open		5
#  define SYS_close		6
#  define SYS_creat		8
#  define SYS_link		9
#  define SYS_unlink		10
#  define SYS_execve		11
#  define SYS_chdir		12
#  define SYS_mknod		14
#  define SYS_chmod		15
#  define SYS_lseek		19
#  define SYS_getpid		20
#  define SYS__mount		21
#  define SYS_ptrace		26
#  define SYS_access		33
#  define SYS_nice		34
#  define SYS_sync		36
#  define SYS_kill		37
#  define SYS_rename		38
#  define SYS_mkdir		39
#  define SYS_rmdir		40
#  define SYS_dup		41
#  define SYS_pipe		42
#  define SYS_times		43
#  define SYS_brk		45
#  define SYS_signal		48
#  define SYS_unmount		52
#  define SYS_ioctl		54
#  define SYS_fcntl		55
#  define SYS_setpgid		57
#  define SYS_umask		60
#  define SYS_chroot		61
#  define SYS_dup2		63
#  define SYS_getppid		64
#  define SYS_getpgrp		65
#  define SYS_setsid		66
#  define SYS_sigaction		67
#  define SYS_sethostname	74
#  define SYS_gettimeofday	78
#  define SYS_symlink		83
#  define SYS_readlink		85
#  define SYS_reboot		88
#  define SYS_munmap		91
#  define SYS_fchmod		94
#  define SYS_fchown		95
#  define SYS_getpriority	96
#  define SYS_setpriority	97
#  define SYS__statfs		99
#  define SYS_setitimer		104
#  define SYS_getitimer		105
#  define SYS_wait4		114
#  define SYS_fsync		118
#  define SYS_uname		122
#  define SYS_mprotect		125
#  define SYS_fchdir		133
#  define SYS_select		142
#  define SYS_flock		143
#  define SYS_mlock		150
#  define SYS_munlock		151
#  define SYS_nanosleep		162
#  define SYS_poll		168
#  define SYS_prctl		172
#  define SYS__getcwd		183
#  define SYS_msgget		186
#  define SYS_msgctl		187
#  define SYS_msgrcv		188
#  define SYS_msgsnd		189
#  define SYS_vfork		190
#  define SYS_getrlimit		191
#  define SYS_utimes		271
#  define SYS_openat		295
#  define SYS_mkdirat		296
#  define SYS_mknodat		297
#  define SYS_fchownat		298
#  define SYS_futimesat		299
#  define SYS_unlinkat		301
#  define SYS_renameat		302
#  define SYS_linkat		303
#  define SYS_symlinkat		304
#  define SYS_readlinkat	305
#  define SYS_fchmodat		306
#  define SYS_faccessat		307
#  define SYS_pselect		308

/* architecture specific: arm */
#  if defined(__arm__)
#   define SYS_lchown		16
#   define SYS_setuid		23
#   define SYS_getuid		24
#   define SYS_setgid		46
#   define SYS_getgid		47
#   define SYS_geteuid		49
#   define SYS_getegid		50
#   define SYS_setreuid		70
#   define SYS_setregid		71
#   define SYS_setrlimit	75
#   define SYS_getrusage	77
#   define SYS_stat		106
#   define SYS_lstat		107
#   define SYS_fstat		108
#   define SYS_sigprocmask	126
#   define SYS_getdents		141
#   define SYS_chown		182
#   define SYS_mmap		192

/* architecture specific: i386 */
#  elif defined(__i386__)
#   define SYS_waitpid	  	7
#   define SYS_alarm		27
#   define SYS_utime		30
#   define SYS_setrlimit	75
#   define SYS_getrusage	77
#   define SYS_mmap		90
#   define SYS__ipc		117
#   define SYS_sigprocmask	175
#   define SYS_truncate		193
#   define SYS_ftruncate	194
#   define SYS_stat		195
#   define SYS_lstat		196
#   define SYS_fstat		197
#   define SYS_lchown		198
#   define SYS_getuid		199
#   define SYS_getgid		200
#   define SYS_geteuid		201
#   define SYS_getegid		202
#   define SYS_setreuid		203
#   define SYS_setregid		204
#   define SYS_chown		212
#   define SYS_setuid		213
#   define SYS_setgid		214
#   define SYS_getdents		220
#   define SYS_set_thread_area	243
#   define SYS_get_thread_area	244
#   define SYS_pselect		270

/* for <sys/shm.h> */
#   define __IPC_SHMAT		21
#   define __IPC_SHMDT		22
#   define __IPC_SHMGET		23
#   define __IPC_SHMCTL		24

#  endif
# endif

#endif /* !KERNEL_LINUX_SYS_SYSCALL_H */
