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
