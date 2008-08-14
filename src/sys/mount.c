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



#include "../syscalls.h"
#include "sys/mount.h"


/* mount */
#ifndef SYS_mount
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
