/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#ifndef KERNEL_WHITIX_COMMON_H
# define KERNEL_WHITIX_COMMON_H


# define SYS_open		0
# define SYS_mkdir		1
# define SYS_close		2
# define SYS_unlink		3
# define SYS_rmdir		4
# define SYS_write		11
# define SYS_read		12
# define SYS_lseek		13
# define SYS_chdir		14
# define SYS_chroot		15
# define SYS_getcwd		19
# define SYS_ioctl		22
# define SYS_sbrk		25
# define SYS_getpid		39
# define SYS_exit		40
# define SYS_waitpid		41

# define SYSL_open		12
# define SYSL_mkdir		8
# define SYSL_close		4
# define SYSL_unlink		4
# define SYSL_rmdir		4
# define SYSL_write		12
# define SYSL_read		12
# define SYSL_lseek		12
# define SYSL_chdir		4
# define SYSL_chroot		4
# define SYSL_getcwd		8
# define SYSL_ioctl		12
# define SYSL_sbrk		4
# define SYSL_getpid		0
# define SYSL_exit		4
# define SYSL_waitpid		8

#endif /* !KERNEL_WHITIX_COMMON_H */
