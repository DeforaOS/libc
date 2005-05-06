/* utime.c */



#include "syscalls.h"
#include "utime.h"


/* time */
syscall2(int, utime, char const *, filename, struct utimbuf const *, buf);
