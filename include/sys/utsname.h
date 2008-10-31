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



#ifndef LIBC_SYS_UTSNAME_H
# define LIBC_SYS_UTSNAME_H

# include "compat/sys/utsname.h"


/* types */
struct utsname
{
	char sysname[_UTSNAME_SYSNAME_SIZE];
	char nodename[_UTSNAME_NODENAME_SIZE];
	char release[_UTSNAME_RELEASE_SIZE];
	char version[_UTSNAME_VERSION_SIZE];
	char machine[_UTSNAME_MACHINE_SIZE];
	char _padding[_UTSNAME_PADDING_SIZE];
};


/* functions */
int uname(struct utsname * name);

#endif /* !LIBC_SYS_UTSNAME_H */
