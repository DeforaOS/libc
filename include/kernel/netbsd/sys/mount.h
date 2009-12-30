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



#ifndef LIBC_KERNEL_NETBSD_SYS_MOUNT_H
# define LIBC_KERNEL_NETBSD_SYS_MOUNT_H


/* constants */
/* mount type */
# define MT_EXT2FS	"ext2fs"
# define MT_EXT3FS	MT_EXT2FS
# define MT_FFS		"ffs"
# define MT_HFS		"hfs"
# define MT_ISO9660	"cd9660"
# define MT_LFS		"lfs"
# define MT_MFS		"mfs"
# define MT_MSDOS	"msdos"
# define MT_NFS		"nfs"
# define MT_NTFS	"ntfs"
# define MT_PROCFS	"procfs"
# define MT_SMBFS	"smbfs"
# define MT_TMPFS	"tmpfs"
# define MT_UFS		MT_FFS

/* mount flags */
# define MF_ASYNC	0x00000040
# define MF_NOATIME	0x04000000
# define MF_NODEV	0x00000010
# define MF_NOEXEC	0x00000004
# define MF_NOSUID	0x00000008
# define MF_RDONLY	0x00000001
# define MF_SYNC	0x00000002

#endif /* !LIBC_KERNEL_NETBSD_SYS_MOUNT_H */
