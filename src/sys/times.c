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
