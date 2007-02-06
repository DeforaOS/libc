/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SYS_TIMES_H
# define LIBC_SYS_TIMES_H

# include "compat/sys/times.h"


/* types */
struct tms
{
	clock_t tms_utime;
	clock_t tms_stime;
	clock_t tms_cutime;
	clock_t tms_cstime;
};


/* function */
clock_t times(struct tms * tmsp);

#endif /* !LIBC_SYS_TIMES_H */
