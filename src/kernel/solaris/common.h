/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef KERNEL_NETBSD_COMMON_H
# define KERNEL_NETBSD_COMMON_H


# define SYS_exit		1
# define SYS_fork		2
# define SYS_read		3
# define SYS_write		4
# define SYS_open		5
# define SYS_close		6
# define SYS_wait		7
# define SYS_link		9
# define SYS_unlink		10
# define SYS_chdir		12
# define SYS_mknod		14
# define SYS_chmod		15
# define SYS_chown		16
# define SYS_brk		17 /* XXX sbrk? */
# define SYS_stat		18
# define SYS_lseek		19
# define SYS_getpid		20
# define SYS_setuid		23
# define SYS_getuid		24
# define SYS_alarm		27
# define SYS_fstat		28
# define SYS_utime		30
# define SYS_access		33
# define SYS_sync		36
# define SYS_kill		37
# define SYS_dup		41
# define SYS_pipe		42
# define SYS_times		43
# define SYS_setgid		46
# define SYS_getgid		47
# define SYS_execve		59
# define SYS_umask		60
# define SYS_fcntl		62
# define SYS_rmdir		79
# define SYS_mkdir		80
# define SYS_lstat		88
# define SYS_symlink		89
# define SYS_readlink		90
# define SYS_fchmod		93
# define SYS_fchown		94
# define SYS_statvfs		103
# define SYS_mmap		115
# define SYS_munmap		117
# define SYS_vfork		119
# define SYS_lchown		130
# define SYS_rename		134
# define SYS_uname		135
# define SYS_gettimeofday	156
# define SYS_nanosleep		199
# define SYS_setreuid		202
# define SYS_setregid		203
# define SYS_getcwd		229
/* FIXME
# define SYS_geteuid		25
# define SYS_getppid		39
# define SYS_getegid		43
# define SYS_symlink		57
# define SYS_setpgid		82
# define SYS_dup2		90
# define SYS_select		93
# define SYS_fchdir		120
# define SYS_mkfifo		132
# define SYS_setsid		147
# define SYS_setgid		181
# define SYS_setegid		182
# define SYS_seteuid		183
# define SYS_sysctl		202 */

#endif /* !KERNEL_NETBSD_COMMON_H */
