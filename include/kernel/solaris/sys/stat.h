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



#ifndef LIBC_KERNEL_SOLARIS_SYS_STAT_H
# define LIBC_KERNEL_SOLARIS_SYS_STAT_H


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
typedef unsigned long dev_t;
# endif
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
typedef long off_t;
# endif
# ifndef time_t
#  define time_t time_t
typedef long time_t;
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
	long padding1[3];
	ino_t st_ino;
	mode_t st_mode;
	nlink_t st_nlink;
	uid_t st_uid;
	gid_t st_gid;
	dev_t st_rdev;
	long padding2[2];
	off_t st_size;
	long padding3;
	time_t st_atime;
	time_t st_mtime;
	time_t st_ctime;
	blksize_t st_blksize;
	blkcnt_t st_blocks;
	char padding4[16];
	long padding5[8];
};

#endif /* !LIBC_KERNEL_SOLARIS_SYS_STAT_H */
