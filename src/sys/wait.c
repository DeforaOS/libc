/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/wait.h"


/* wait */
#ifndef SYS_wait
pid_t wait(int * status)
{
	return waitpid(-1, status, 0);
}
#endif /* !SYS_wait */


/* waitpid */
#if !defined(SYS_waitpid) && defined(SYS_wait4)
# include "stdlib.h"
pid_t wait4(pid_t pid, int * status, int options, void * rusage);
pid_t waitpid(pid_t pid, int * status, int options)
{
	return wait4(pid, status, options, NULL);
}
#endif
