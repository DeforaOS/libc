/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "sys/time.h"
#include "stdlib.h"
#include "syscalls.h"
#include "time.h"


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
