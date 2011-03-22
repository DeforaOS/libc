/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
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



#include "../syscalls.h"
#include "sys/mount.h"


/* mount */
#if !defined(SYS_mount) && defined(SYS__mount) /* for Linux */
int _mount(char const * node, char const * dir, char const * type, int flags,
		char const * data);

int mount(char const * type, char const * dir, int flags, const void * data,
		size_t data_len)
{
	/* FIXME really implement */
	return _mount(NULL, dir, type, flags, NULL);
}
#elif !defined(SYS_mount)
# warning Unsupported platform: mount() is missing
# include "errno.h"
int mount(char const * type, char const * dir, int flags, const void * data,
		size_t data_len)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* umount */
#ifndef SYS_unmount
# warning Unsupported platform: unmount() is missing
# include "errno.h"
int unmount(char const * dir, int flags)
{
	errno = ENOSYS;
	return -1;
}
#endif
