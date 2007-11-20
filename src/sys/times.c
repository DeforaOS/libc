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
#include "sys/times.h"


/* functions */
/* times */
#if !defined(SYS_times)
# if defined(SYS_gettimeofday) && defined(SYS_getrusage)
#  include "sys/resource.h"
#  include "sys/time.h"
#  include "stdlib.h"
clock_t times(struct tms * tmsp) /* FIXME should be in ticks */
{
	struct timeval tv;
	struct rusage ru;

	if(gettimeofday(&tv, NULL) != 0 || getrusage(RUSAGE_SELF, &ru) == -1)
		return -1;
	if(tmsp != NULL)
	{
		tmsp->tms_utime = ru.ru_utime.tv_sec;
		tmsp->tms_stime = ru.ru_stime.tv_sec;
	}
	if(getrusage(RUSAGE_CHILDREN, &ru) == -1)
		return -1;
	if(tmsp != NULL)
	{
		tmsp->tms_cutime = tmsp->tms_utime + ru.ru_utime.tv_sec;
		tmsp->tms_cstime = tmsp->tms_stime + ru.ru_stime.tv_sec;
	}
	return tv.tv_sec != (clock_t)-1 ? tv.tv_sec : 0;
}
# else /* !SYS_times && !(SYS_gettimeofday && SYS_getrusage) */
#  warning Unsupported platform: times() is missing
# endif
#endif /* !SYS_times */
