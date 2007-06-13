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



#include "syscalls.h"
#include "utime.h"


/* utime */
#if !defined(SYS_utime) && defined(SYS_utimes)
# include "sys/time.h"
# include "stdlib.h"
int utime(char const * filename, struct utimbuf const * times)
{
	struct timeval tv[2];

	if(times == NULL)
		return utimes(filename, NULL);
	tv[0].tv_sec = times->actime;
	tv[0].tv_usec = 0;
	tv[1].tv_sec = times->modtime;
	tv[1].tv_usec = 0;
	return utimes(filename, tv);
}
#endif /* !SYS_utime && SYS_utimes */
