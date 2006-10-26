/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/wait.h"


/* wait */
pid_t wait(int * status)
{
	return waitpid(-1, status, 0);
}


/* waitpid */
#ifndef __NetBSD__
syscall3(pid_t, waitpid, pid_t, pid, int *, status, int, options)
#endif
