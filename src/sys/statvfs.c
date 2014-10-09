/* $Id$ */
/* Copyright (c) 2008 Pierre Pronchery <khorben@defora.org> */
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



#include "string.h"
#include "errno.h"
#include "../syscalls.h"
#include "sys/statvfs.h"


/* fstatvfs */
int fstatvfs(int fd, struct statvfs * buf)
{
	/* FIXME implement */
	errno = ENOSYS;
	return -1;
}


/* statvfs */
#if !defined(SYS_statvfs)
# if defined(SYS__statfs)
typedef long fsid_t;
struct statfs
{
	long f_type;
	long f_bsize;
	long f_blocks;
	long f_bfree;
	long f_bavail;
	long f_files;
	long f_ffree;
	fsid_t f_fsid;
	long f_namelen;
};
extern int _statfs(char const * path, struct statfs * buf);
int statvfs(char const * path, struct statvfs * buf)
{
	struct statfs fs;

	if(_statfs(path, &fs) != 0)
		return -1;
	memset(buf, 0, sizeof(*buf));
	buf->f_bsize = fs.f_bsize;
	buf->f_blocks = fs.f_blocks;
	buf->f_bfree = fs.f_bfree;
	buf->f_bavail = fs.f_bavail;
	buf->f_files = fs.f_files;
	buf->f_ffree = fs.f_ffree;
	buf->f_fsid = fs.f_fsid;
	buf->f_namemax = fs.f_namelen;
	return 0;
}
# else /* !SYS_statvfs && !SYS__statfs */
#  warning Unsupported platform: statvfs() is missing
int statvfs(char const * path, struct statvfs * buf)
{
	errno = ENOSYS;
	return -1;
}
# endif
#endif
