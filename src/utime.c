/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



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
