/* fcntl.c */



#include "syscalls.h"
#include "fcntl.h"


/* open */
syscall3(int, open, char const *, filename, int, flags, mode_t, mode);
