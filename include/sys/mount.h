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



#ifndef LIBC_SYS_MOUNT_H
# define LIBC_SYS_MOUNT_H


/* types */
# ifndef size_t
#  define size_t size_t
typedef unsigned long size_t;
# endif

# include "../compat/sys/mount.h"


/* functions */
int mount(char const * type, char const * dir, int flags, const void * data,
		size_t data_len);
int unmount(char const * dir, int flags);

#endif /* !LIBC_SYS_MOUNT_H */
