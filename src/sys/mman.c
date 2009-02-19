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



#include "errno.h"
#include "../syscalls.h"
#include "sys/mman.h"


/* mlock */
#ifndef SYS_mlock
# warning Unsupported platform: mlock() is missing
int mlock(const void * addr, size_t length)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* mmap */
#ifndef SYS_mmap
# warning Unsupported platform: mmap() is missing
void * mmap(void * addr, size_t length, int prot, int flags, int fd,
		off_t offset)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* mprotect */
#ifndef SYS_mprotect
# warning Unsupported platform: mprotect() is missing
int mprotect(void * addr, size_t length, int prot)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* munlock */
#ifndef SYS_munlock
# warning Unsupported platform: munlock() is missing
int munlock(const void * addr, size_t length)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* munmap */
#ifndef SYS_munmap
# warning Unsupported platform: munmap() is missing
int munmap(void * addr, size_t length)
{
	errno = ENOSYS;
	return -1;
}
#endif
