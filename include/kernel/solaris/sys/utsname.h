/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_SOLARIS_SYS_UTSNAME_H
# define LIBC_KERNEL_SOLARIS_SYS_UTSNAME_H


/* struct utsname */
# define _UTSNAME_SIZE			257
# define _UTSNAME_SYSNAME_SIZE		_UTSNAME_SIZE
# define _UTSNAME_NODENAME_SIZE		_UTSNAME_SIZE
# define _UTSNAME_RELEASE_SIZE		_UTSNAME_SIZE
# define _UTSNAME_VERSION_SIZE		_UTSNAME_SIZE
# define _UTSNAME_MACHINE_SIZE		_UTSNAME_SIZE
# define _UTSNAME_PADDING_SIZE		_UTSNAME_SIZE

#endif /* !LIBC_KERNEL_SOLARIS_SYS_UTSNAME_H */
