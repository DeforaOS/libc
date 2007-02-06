/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "unistd.h"
#include "syscalls.h"
#include "signal.h"


/* kill */
#ifndef SYS_kill
# warning Unsupported platform: kill() is missing
#endif


/* raise */
int raise(int sig)
{
	return kill(getpid(), sig);
}
