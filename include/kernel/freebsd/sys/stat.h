/* $Id$ */
/* Copyright (c) 2007 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* libc is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * libc is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with libc; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



#ifndef LIBC_KERNEL_FREEBSD_SYS_STAT_H
# define LIBC_KERNEL_FREEBSD_SYS_STAT_H


/* types */
# ifndef blkcnt_t
#  define blkcnt_t blkcnt_t
typedef unsigned long long blkcnt_t;
# endif
# ifndef blksize_t
#  define blksize_t blksize_t
typedef int blksize_t;
# endif
# ifndef dev_t
#  define dev_t dev_t
typedef unsigned int dev_t;
# endif
# ifndef gid_t
#  define gid_t gid_t
typedef unsigned int gid_t;
# endif
# ifndef id_t
#  define id_t id_t
typedef unsigned long long id_t;
# endif
# ifndef ino_t
#  define ino_t ino_t
typedef unsigned int ino_t;
# endif
# ifndef mode_t
#  define mode_t mode_t
typedef unsigned short mode_t;
# endif
# ifndef nlink_t
#  define nlink_t nlink_t
typedef short int nlink_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef unsigned int time_t;
# endif
# ifndef uid_t
#  define uid_t uid_t
typedef unsigned int uid_t;
# endif

struct stat
{
	dev_t st_dev;
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	time_t st_atime;
	long _padding1;
	time_t st_mtime;
	long _padding2;
	time_t st_ctime;
	long _padding3;
	off_t st_size;
	blkcnt_t st_blocks;
	blksize_t st_blksize;
	char _padding4[24]; /* FIXME incorrect */
};

#endif /* !LIBC_KERNEL_FREEBSD_SYS_STAT_H */
