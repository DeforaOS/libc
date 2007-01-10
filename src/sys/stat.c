/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



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


/* mkfifo */
#ifdef SYS_mkfifo
syscall2(int, mkfifo, char const *, path, mode_t, mode);
#else
int mkfifo(char const * path, mode_t mode)
{
	return mknod(path, mode | S_IFIFO, 0);
}
#endif


/* mknod */
syscall3(int, mknod, char const *, path, mode_t, mode, dev_t, dev);


/* stat */
syscall2(int, stat, char const *, filename, struct stat *, buf);


/* umask */
syscall1(mode_t, umask, mode_t, mask);
