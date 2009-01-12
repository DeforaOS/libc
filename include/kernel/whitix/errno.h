/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#ifndef LIBC_KERNEL_WHITIX_ERRNO_H
# define LIBC_KERNEL_WHITIX_ERRNO_H


/* constants */
# define EPERM		1
# define ENOENT		2
# define EIO		3
# define EBADF		4
# define ENOMEM		5
# define EACCES		6
# define EBUSY		7
# define EFAULT		8
# define EEXIST		9
# define EMFILE		10
# define ENOSPC		11
# define EROFS		12
# define ENOSYS		13
# define ENOTDIR	15
# define EISDIR		17
# define EINVAL		18
# define EINTR		19
# define E2BIG		20
# define EAGAIN		22
# define ECHILD		23
# define ENOEXEC	24
# define EPIPE		32
# define ENOTTY		37
# define ENOBUFS	45
# define EXDEV		52
# define ERANGE		56
# define ENODEV		59

#endif /* !LIBC_KERNEL_WHITIX_ERRNO_H */
