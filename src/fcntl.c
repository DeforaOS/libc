/* fcntl.c */



#include "syscalls.h"
#include "fcntl.h"


/* open */
int open(char const * filename, int flags, ...)
{
	_syscall3(SYS_open, filename, flags, 0); /* FIXME */
}
