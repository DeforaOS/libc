/* $Id$ */
/* Copyright (c) 2006 The DeforaOS Project */



#ifndef LIBC_SYS_STATVFS_H
# define LIBC_SYS_STATVFS_H

# include "compat/sys/types.h"


/* types */
struct statvfs
{
	unsigned long f_bsize;
	unsigned long f_frsize;
	fsblkcnt_t f_blocks;
	fsblkcnt_t f_bfree;
	fsblkcnt_t f_bavail;
	fsfilcnt_t f_files;
	fsfilcnt_t f_ffree;
	fsfilcnt_t f_favail;
	unsigned long f_fsid;
	unsigned long f_flag;
	unsigned long f_namemax;
};

/* functions */
int statvfs(char const * path, struct statvfs * buf);
int fstatvfs(int fd, struct statvfs * buf);

#endif /* !LIBC_SYS_STATVFS_H */
