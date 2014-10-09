/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
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



#ifndef LIBC_KERNEL_NETBSD_SYS_MOUNT_H
# define LIBC_KERNEL_NETBSD_SYS_MOUNT_H

# include <sys/stat.h> /* XXX either one should not be included */
# include <sys/types.h>


/* types */
struct export_args30
{
	int ex_flags;
	uid_t ex_root;
	/* struct uucred ex_anon; */
	unsigned short ex_anon_cr_unused;
	uid_t ex_anon_cr_uid;
	gid_t ex_anon_cr_gid;
	short ex_anon_cr_ngroups;
	gid_t ex_anon_cr_groups[16];
	void * ex_addr;
	int ex_addrlen;
	void * ex_mask;
	int ex_masklen;
	void * ex_indexfile;
};

struct iso_args
{
	char * fspec;
	struct export_args30 _padding0;
	int flags;
};
# define MT_ISO9660	"cd9660"

struct hfs_args
{
	char * fspec;
};
# define MT_HFS		"hfs"

struct mfs_args
{
	char * fspec;
	struct export_args30 _padding0;
	void * base;
	unsigned long size;
};
# define MT_MFS		"mfs"

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
# define NFS_ARGSVERSION 3
# define MT_NFS		"nfs"

struct ntfs_args
{
	char * fspec;
	struct export_args30 _padding0;
	uid_t uid;
	gid_t gid;
	mode_t mode;
	unsigned long flag;
};
# define MT_NTFS	"ntfs"

struct procfs_args
{
	int version;
	int flags;
};
# define PROCFS_ARGS_VERSION 1
# define MT_PROCFS	"procfs"

struct tmpfs_args
{
	int ta_version;
	ino_t ta_nodes_max;
	off_t ta_size_max;
	uid_t ta_root_uid;
	gid_t ta_root_gid;
	mode_t ta_root_mode;
};
# define TMPFS_ARGS_VERSION 1
# define MT_TMPFS	"tmpfs"

struct ufs_args
{
	char * fspec;
};
# define MT_FFS		"ffs"
# define MT_UFS		MT_FFS


/* constants */
/* mount type */
# define MT_EXT2FS	"ext2fs"
# define MT_EXT3FS	MT_EXT2FS
# define MT_LFS		"lfs"
# define MT_MSDOS	"msdos"
# define MT_SMBFS	"smbfs"

/* mount flags */
# define MF_ASYNC	0x00000040
# define MF_FORCE	0x00080000
# define MF_NOATIME	0x04000000
# define MF_NODEV	0x00000010
# define MF_NOEXEC	0x00000004
# define MF_NOSUID	0x00000008
# define MF_REMOUNT	0x00010000
# define MF_RDONLY	0x00000001
# define MF_SYNC	0x00000002

#endif /* !LIBC_KERNEL_NETBSD_SYS_MOUNT_H */
