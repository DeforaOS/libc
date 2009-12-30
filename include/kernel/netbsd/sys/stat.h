/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System libc */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#ifndef LIBC_KERNEL_NETBSD_SYS_STAT_H
# define LIBC_KERNEL_NETBSD_SYS_STAT_H


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
# ifndef id_t
#  define id_t id_t
typedef unsigned int id_t;
# endif
# ifndef ino_t
#  define ino_t ino_t
typedef unsigned int ino_t;
# endif
# ifndef mode_t
#  define mode_t mode_t
typedef int mode_t;
# endif
# ifndef nlink_t
#  define nlink_t nlink_t
typedef int nlink_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef int time_t;
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
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
#ifdef _LP64
	int _padding1;
#endif
	time_t st_atime;
#ifdef _LP64
	int _padding2;
#endif
	long _padding3;
	time_t st_mtime;
#ifdef _LP64
	int _padding4;
#endif
	long _padding5;
	time_t st_ctime;
#ifdef _LP64
	int _padding6;
#endif
	long _padding7;
	off_t st_size;
	blkcnt_t st_blocks;
	blksize_t st_blksize;
	char _padding8[12];
	time_t _padding9;
#ifdef _LP64
	int _padding10;
#endif
	long _padding11;
#ifndef _LP64
	int _padding12;
#endif
};

#endif /* !LIBC_KERNEL_NETBSD_SYS_STAT_H */
