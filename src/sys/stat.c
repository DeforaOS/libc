/* sys/stat.c */



#include "sys/stat.h"
#include "../syscalls.h"


/* fstat */
syscall2(int, fstat, int, fd, struct stat *, buf);


/* lstat */
syscall2(int, lstat, char const *, filename, struct stat *, buf);


/* stat */
syscall2(int, stat, char const *, filename, struct stat *, buf);
