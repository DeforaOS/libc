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



#include "errno.h"
#include "../syscalls.h"
#include "sys/mman.h"


/* mlock */
#ifndef SYS_mlock
# warning Unsupported platform: mlock() is missing
int mlock(const void * addr, size_t len)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* mmap */
#ifndef SYS_mmap
# warning Unsupported platform: mmap() is missing
void * mmap(void * addr, size_t len, int prot, int flags, int fd, off_t offset)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* munlock */
#ifndef SYS_munlock
# warning Unsupported platform: munlock() is missing
int munlock(const void * addr, size_t len)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* munmap */
#ifndef SYS_munmap
# warning Unsupported platform: munmap() is missing
int munmap(void * addr, size_t len)
{
	errno = ENOSYS;
	return -1;
}
#endif
