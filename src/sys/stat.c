/* sys/stat.c */



#include "sys/stat.h"
#include "../syscalls.h"


/* lstat */
syscall2(int, lstat, char const *, filename, struct stat *, buf);


/* stat */
syscall2(int, stat, char const *, filename, struct stat *, buf);
