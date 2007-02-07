/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_LINUX_SYS_STAT_H
# define LIBC_KERNEL_LINUX_SYS_STAT_H


/* types */
# ifndef blkcnt_t
#  define blkcnt_t blkcnt_t
typedef unsigned long blkcnt_t;
# endif
# ifndef blksize_t
#  define blksize_t blksize_t
typedef unsigned long blksize_t;
# endif
# ifndef dev_t
#  define dev_t dev_t
typedef unsigned short int dev_t;
#endif
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif
# ifndef ino_t
#  define ino_t ino_t
typedef unsigned long ino_t;
# endif
# ifndef mode_t
#  define mode_t mode_t
typedef unsigned int mode_t;
# endif
# ifndef nlink_t
#  define nlink_t nlink_t
typedef unsigned int nlink_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef unsigned int time_t;
# endif

# ifndef gid_t
#  define gid_t gid_t
typedef id_t gid_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef id_t uid_t;
# endif

struct stat
{
	dev_t st_dev;
	char _padding1[10];
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	char _padding2[10];
	off_t st_size;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
	long _padding3;
	time_t st_atime;
	int _padding4;
	time_t st_mtime;
	int _padding5;
	time_t st_ctime;
	unsigned long _padding6;
	unsigned long long _padding7;
};

#endif /* !LIBC_KERNEL_LINUX_SYS_STAT_H */
