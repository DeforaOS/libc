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
# define NFS_ARGSVERSION 0

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
# define MF_FORCE	0x00000001	/* FIXME only valid for unmount() */
# define MF_NOATIME	0x00000400
# define MF_NODEV	0x00000004
# define MF_NOEXEC	0x00000008
# define MF_NOSUID	0x00000002
# define MF_RDONLY	0x00000001
# define MF_REMOUNT	0x00000020
# define MF_SYNC	0x00000010

#endif /* !LIBC_KERNEL_LINUX_SYS_MOUNT_H */
