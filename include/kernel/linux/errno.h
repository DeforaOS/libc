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



#ifndef LIBC_KERNEL_LINUX_ERRNO_H
# define LIBC_KERNEL_LINUX_ERRNO_H


/* constants */
# define EPERM		1
# define ENOENT		2
# define EINTR		4
# define EIO		5
# define E2BIG		7
# define ENOEXEC	8
# define EBADF		9
# define ECHILD		10
# define EAGAIN		11
# define ENOMEM		12
# define EACCES		13
# define EFAULT		14
# define EBUSY		16
# define EEXIST		17
# define EXDEV		18
# define ENODEV		19
# define ENOTDIR	20
# define EISDIR		21
# define EINVAL		22
# define ENOTTY		25
# define ENOSPC		28
# define EROFS		30
# define EPIPE		32
# define ERANGE		34
# define ENOSYS		38
# define ELOOP		40
# define ENOBUFS	105

#endif /* !LIBC_KERNEL_LINUX_ERRNO_H */
