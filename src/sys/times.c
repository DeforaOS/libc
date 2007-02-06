/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



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
	tmsp->tms_utime = ru.ru_utime.tv_sec;
	tmsp->tms_stime = ru.ru_stime.tv_sec;
	if(getrusage(RUSAGE_CHILDREN, &ru) == -1)
		return -1;
	tmsp->tms_cutime = tmsp->tms_utime + ru.ru_utime.tv_sec;
	tmsp->tms_cstime = tmsp->tms_stime + ru.ru_stime.tv_sec;
	return tv.tv_sec != (clock_t)-1 ? tv.tv_sec : 0;
}
# else /* !SYS_times && !(SYS_gettimeofday && SYS_getrusage) */
#  warning Unsupported platform: times() is missing
# endif
#endif /* !SYS_times */
