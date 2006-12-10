/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SYS_TIMES_H
# define LIBC_SYS_TIMES_H


/* types */
# ifndef clock_t
#  define clock_t clock_t
typedef int clock_t;
# endif

struct tms
{
	clock_t tms_utime;
	clock_t tms_stime;
	clock_t tms_cutime;
	clock_t tms_cstime;
};


/* function */
clock_t times(struct tms * buf);

#endif /* !LIBC_SYS_TIMES_H */
