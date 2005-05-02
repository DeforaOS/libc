/* sys/utsname.c */



#include "../syscalls.h"
#include "sys/utsname.h"


/* uname */
syscall1(int, uname, struct utsname *, utsname);
