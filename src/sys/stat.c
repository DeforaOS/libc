/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#include "../syscalls.h"
#include "sys/stat.h"


/* chmod */
#ifndef SYS_chmod
# warning Unsupported platform: chmod() is missing
#endif


/* fstat */
#ifndef SYS_fstat
# warning Unsupported platform: fstat() is missing
#endif


/* lstat */
#ifndef SYS_lstat
# warning Unsupported platform: lstat() is missing
#endif


/* mkdir */
#ifndef SYS_mkdir
# warning Unsupported platform: mkdir() is missing
#endif


/* mkfifo */
#if !defined(SYS_mkfifo)
# if defined(SYS_mknod)
int mkfifo(char const * path, mode_t mode)
{
	return mknod(path, mode | S_IFIFO, 0);
}
# else /* !SYS_mkfifo && !SYS_mknod */
#  warning Unsupported platform: mkfifo() is missing
# endif
#endif /* !SYS_mkfifo */


/* mknod */
#ifndef SYS_mknod
# warning Unsupported platform: mknod() is missing
#endif


/* stat */
#ifndef SYS_stat
# warning Unsupported platform: stat() is missing
#endif


/* umask */
#ifndef SYS_umask
# warning Unsupported platform: umask() is missing
#endif
