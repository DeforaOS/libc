/* utime.c */



#include "syscalls.h"
#include "utime.h"


/* time */
#ifndef __NetBSD__
syscall2(int, utime, char const *, filename, struct utimbuf const *, buf);
#endif
