/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "stdarg.h"
#include "syscalls.h"
#include "fcntl.h"


/* open */
int open(char const * filename, int flags, ...)
{
	va_list arg;
	mode_t mode;

	if(flags & O_CREAT)
	{
		va_start(arg, flags);
		mode = va_arg(arg, mode_t);
		va_end(arg);
	}
	return _syscall3(SYS_open, (int)filename, flags, mode);
}
