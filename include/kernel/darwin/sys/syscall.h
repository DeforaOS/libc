/* $Id$ */
/* Copyright (c) 2016-2021 Pierre Pronchery <khorben@defora.org> */
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



#ifndef KERNEL_DARWIN_SYS_SYSCALL_H
# define KERNEL_DARWIN_SYS_SYSCALL_H


# define SYS_exit		1
# define SYS_fork		2
# define SYS_read		3
# define SYS_write		4
# define SYS_open		5
# define SYS_close		6
# define SYS_wait4		7
# define SYS_link		9
# define SYS_unlink		10
# define SYS_chdir		12
# define SYS_fchdir		13
# define SYS_mknod		14
# define SYS_chmod		15
# define SYS_chown		16
# define SYS_getpid		20
# define SYS_setuid		23
# define SYS_getuid		24
# define SYS_geteuid		25
# define SYS_ptrace		26
# define SYS_access		33
# define SYS_sync		36
# define SYS_kill		37
# define SYS_getppid		39
# define SYS_dup		41
# define SYS_pipe		42
# define SYS_getegid		43
# define SYS_getgid		47
# define SYS_ioctl		54
# define SYS_reboot		55
# define SYS_symlink		57
# define SYS_readlink		58
# define SYS_execve		59
# define SYS_umask		60
# define SYS_chroot		61
# define SYS_vfork		66
# define SYS_munmap		73
# define SYS_mprotect		74
# define SYS_getpgrp		81
# define SYS_setpgid		82
# define SYS_dup2		90
# define SYS_fcntl		92
# define SYS_select		93
# define SYS_fsync		95
# define SYS_setpriority	96
# define SYS_getpriority	100
# define SYS_gettimeofday	116
# define SYS_getrusage		117
# define SYS_fchown		123
# define SYS_fchmod		124
# define SYS_setreuid		126
# define SYS_setregid		127
# define SYS_rename		128
# define SYS_flock		131
# define SYS_mkfifo		132
# define SYS_mkdir		136
# define SYS_rmdir		137
# define SYS_utimes		138
# define SYS_setsid		147
# define SYS_unmount		159
# define SYS_setgid		181
# define SYS_stat		188
# define SYS_fstat		189
# define SYS_lstat		190
# define SYS_getrlimit		194
# define SYS_setrlimit		195
# define SYS_getdents		196
# define SYS_mmap		197
# define SYS_lseek		199
# define SYS_truncate		200
# define SYS_ftruncate		201
# define SYS_sysctl		202
# define SYS_mlock		203
# define SYS_munlock		204
# define SYS_shmctl		263
# define SYS_lchown		364
# define SYS_openat		463
# define SYS_renameat		465
# define SYS_faccessat		466
# define SYS_fchmodat		467
# define SYS_fchownat		468
# define SYS_fstatat		469
# define SYS_linkat		471
# define SYS_unlinkat		472
# define SYS_readlinkat		473
# define SYS_symlinkat		474
# define SYS_mkdirat		475

#endif /* !KERNEL_DARWIN_SYS_SYSCALL_H */
