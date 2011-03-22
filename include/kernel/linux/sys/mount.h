/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_LINUX_SYS_MOUNT_H
# define LIBC_KERNEL_LINUX_SYS_MOUNT_H

# include <sys/stat.h> /* XXX either one should not be included */
# include <sys/types.h>


/* types */
struct iso_args
{
	char * fspec;
	int flags;
};

struct nfs_args
{
	int version;
	void * addr;
	int addrlen;
	int sotype;
	int proto;
	void * fh;
	int fhsize;
	int flags;
	int wsize;
	int rsize;
	int readdirsize;
	int timeo;
	int retrans;
	int maxgrouplist;
	int readahead;
	int leaseterm;
	int deadthresh;
	char * hostname;
};

struct ntfs_args
{
	char * fspec;
	uid_t uid;
	gid_t gid;
	mode_t mode;
	unsigned long flag;
};

struct procfs_args
{
	int version;
	int flags;
};
# define PROCFS_ARGS_VERSION 0

struct ufs_args
{
	char * fspec;
};


/* constants */
/* mount type */
# define MT_EXT2FS	"ext2"
# define MT_EXT3FS	MT_EXT2FS
# define MT_FFS		MT_UFS
# define MT_ISO9660	"iso9660"
# define MT_MSDOS	"vfat"
# define MT_NFS		"nfs"
# define MT_NTFS	"ntfs"
# define MT_PROCFS	"proc"
# define MT_SMBFS	"smb"
# define MT_UFS		"ufs"

/* mount flags */
# define MF_ASYNC	0x00000000
# define MF_NOATIME	0x00000400
# define MF_NODEV	0x00000004
# define MF_NOEXEC	0x00000008
# define MF_NOSUID	0x00000002
# define MF_RDONLY	0x00000001
# define MF_SYNC	0x00000010

#endif /* !LIBC_KERNEL_LINUX_SYS_MOUNT_H */
