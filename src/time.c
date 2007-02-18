/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "sys/time.h"
#include "stdlib.h"
#include "errno.h"
#include "syscalls.h"
#include "time.h"


/* nanosleep */
#ifndef SYS_nanosleep
# warning Unsupported platform: nanosleep() is missing
#endif


/* localtime */
struct tm * localtime(time_t const * t)
{
	static struct tm ret;

	tzset();
	if(localtime_r(t, &ret) == NULL)
		return NULL;
	return &ret;
}


/* localtime_r */
struct tm * localtime_r(time_t const * t, struct tm * ret)
{
	/* FIXME implement */
	errno = ENOSYS;
	return NULL;
}


/* strftime */
size_t strftime(char * s, size_t maxsize, char const * format,
		struct tm * timep)
{
	/* FIXME implement */
	if(maxsize > 0)
		*s = '\0';
	errno = ENOSYS;
	return 0;
}


/* time */
time_t time(time_t * t)
{
	struct timeval tv;

	if(gettimeofday(&tv, NULL) != 0)
		return -1;
	if(t != NULL)
		*t = tv.tv_sec;
	return tv.tv_sec;
}


/* tzset */
void tzset(void)
{
	/* FIXME implement */
}
