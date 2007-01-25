/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/stat.h"


/* chmod */


/* fstat */


/* lstat */


/* mkdir */


/* mkfifo */
#ifndef SYS_mkfifo
int mkfifo(char const * path, mode_t mode)
{
	return mknod(path, mode | S_IFIFO, 0);
}
#endif


/* mknod */


/* stat */


/* umask */
