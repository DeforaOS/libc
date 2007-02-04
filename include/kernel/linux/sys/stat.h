/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_LINUX_SYS_STAT_H
# define LIBC_KERNEL_LINUX_SYS_STAT_H


/* types */
struct stat
{
	dev_t st_dev;
	short int padding1;
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	short int padding2;
	off_t st_size;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
	char padding[8];
};

#endif /* !LIBC_KERNEL_LINUX_SYS_STAT_H */
