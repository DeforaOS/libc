/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



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
