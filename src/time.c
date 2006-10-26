/* time.c */



#include "syscalls.h"
#include "time.h"


/* time */
#ifndef __NetBSD__
syscall1(time_t, time, time_t *, t);
#endif
