/* sys/stat.c */



#include "../syscalls.h"
#include "sys/stat.h"


/* chmod */
syscall2(int, chmod, char const *, path, mode_t, mode);


/* fstat */
syscall2(int, fstat, int, fd, struct stat *, buf);


/* lstat */
syscall2(int, lstat, char const *, filename, struct stat *, buf);


/* mkdir */
syscall2(int, mkdir, char const *, name, mode_t, mode);


/* stat */
syscall2(int, stat, char const *, filename, struct stat *, buf);


/* umask */
syscall1(mode_t, umask, mode_t, mask);
