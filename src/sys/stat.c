/* $Id$ */
/* Copyright (c) 2005-2015 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#include "errno.h"
#include "../syscalls.h"
#include "sys/stat.h"


/* chmod */
#ifndef SYS_chmod
# warning Unsupported platform: chmod() is missing
int chmod(char const * name, mode_t mode)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* fchmod */
#ifndef SYS_fchmod
# warning Unsupported platform: fchmod() is missing
int fchmod(int fildes, mode_t mode)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* fstat */
#ifndef SYS_fstat
# warning Unsupported platform: fstat() is missing
int fstat(int fildes, struct stat * st)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* lstat */
#ifndef SYS_lstat
# warning Unsupported platform: lstat() is missing
int lstat(char const * pathname, struct stat * st)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* mkdir */
#ifndef SYS_mkdir
# warning Unsupported platform: mkdir() is missing
int mkdir(char const * name, mode_t mode)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* mkdirat */
#ifndef SYS_mkdirat
# warning Unsupported platform: mkdirat() is missing
int mkdirat(int fd, char const * name, mode_t mode)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* mkfifo */
#if !defined(SYS_mkfifo)
# if defined(SYS_mknod) && defined(S_IFIFO)
int mkfifo(char const * path, mode_t mode)
{
	return mknod(path, mode | S_IFIFO, 0);
}
# else /* !SYS_mkfifo && !SYS_mknod */
#  warning Unsupported platform: mkfifo() is missing
int mkfifo(char const * path, mode_t mode)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif /* !SYS_mkfifo */


/* mkfifoat */
#if !defined(SYS_mkfifoat)
# if defined(SYS_mknodat) && defined(S_IFIFO)
int mkfifoat(int fd, char const * path, mode_t mode)
{
	return mknodat(fd, path, mode | S_IFIFO, 0);
}
# else /* !SYS_mkfifoat && !SYS_mknodat */
#  warning Unsupported platform: mkfifoat() is missing
int mkfifoat(int fd, char const * path, mode_t mode)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif /* !SYS_mkfifoat */


/* mknod */
#ifndef SYS_mknod
# warning Unsupported platform: mknod() is missing
int mknod(char const * name, mode_t mode, dev_t dev)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* mknodat */
#ifndef SYS_mknodat
# warning Unsupported platform: mknodat() is missing
int mknodat(int fd, char const * name, mode_t mode, dev_t dev)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* stat */
#ifndef SYS_stat
# warning Unsupported platform: stat() is missing
int stat(char const * pathname, struct stat * st)
{
	errno = ENOSYS;
	return -1;
}
#endif


/* umask */
#ifndef SYS_umask
# warning Unsupported platform: umask() is missing
#endif
