/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



#ifndef KERNEL_OPENBSD_COMMON_H
# define KERNEL_OPENBSD_COMMON_H


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
# define SYS_access		33
# define SYS_sync		36
# define SYS_kill		37
# define SYS_getppid		39
# define SYS_dup		41
# define SYS_getegid		43
# define SYS_getgid		47
# define SYS_getlogin		49
# define SYS_setlogin		50
# define SYS_ioctl		54
# define SYS_symlink		57
# define SYS_readlink		58
# define SYS_execve		59
# define SYS_umask		60
# define SYS_vfork		66
# define SYS_brk		69
# define SYS_munmap		73
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
# define SYS_mkfifo		132
# define SYS_mkdir		136
# define SYS_rmdir		137
# define SYS_utimes		138
# define SYS_setsid		147
# define SYS_setgid		181
# define SYS_setegid		182
# define SYS_seteuid		183
# define SYS_getrlimit		194
# define SYS_setrlimit		195
# define SYS_getdirentries	196
# define SYS_mmap		197
# define SYS_lseek		199
# define SYS_getpgid		207
# define SYS_nanosleep		240
# define SYS_lchown		254
# define SYS__statfs		261
# define SYS_pipe		263
# define SYS_stat		291
# define SYS_fstat		292
# define SYS_lstat		293
# define SYS_getcwd		304

#endif /* !KERNEL_OPENBSD_COMMON_H */
