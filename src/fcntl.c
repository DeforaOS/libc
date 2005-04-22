/* fcntl.c */



#include "stdarg.h"
#include "syscalls.h"
#include "fcntl.h"


/* open */
int open(char const * filename, int flags, ...)
{
	va_list arg;
	int ret;

	va_start(arg, flags);
	ret = _syscall3(SYS_open, (int)filename, flags, (int)arg);
	va_end(arg);
	return ret;
}
