/* signal.c */



#include "syscalls.h"
#include "signal.h"


/* kill */
syscall2(int, kill, pid_t, pid, int, sig);
