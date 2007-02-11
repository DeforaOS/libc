/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "sys/ioctl.h"
#include "errno.h"
#include "syscalls.h"
#include "termios.h"


/* tcgetattr */
int tcgetattr(int fildes, struct termios * tp)
{
#if defined(TCGETS)
	return ioctl(fildes, TCGETS, tp);
#elif defined(TIOCGETA)
	return ioctl(fildes, TIOCGETA, tp);
#else
	errno = ENOSYS;
	return -1;
#endif
}
