/* sys/times.c */



#include "../syscalls.h"
#include "sys/times.h"


/* times */
syscall1(clock_t, times, struct tms *, buf);
