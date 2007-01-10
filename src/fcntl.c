/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "stdarg.h"
#include "errno.h"
#include "syscalls.h"
#include "fcntl.h"


/* fcntl */
int fcntl(int fd, int cmd, ...)
{
	int ret;
	va_list arg;

	switch(cmd)
	{
		case F_DUPFD:
		case F_GETFD:
		case F_GETFL:
		case F_GETOWN:
			return _syscall2(SYS_fcntl, fd, cmd);
		case F_SETFD:
		case F_SETFL:
		case F_SETOWN:
		case F_GETLK:
		case F_SETLK:
			va_start(arg, cmd);
			ret = _syscall3(SYS_fcntl, fd, cmd, va_arg(arg, int));
			va_end(arg);
			return ret;
	}
	errno = EINVAL;
	return -1;
}


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
