/* $Id$ */
/* Copyright (c) 2007 The DeforaOS Project */



#ifndef LIBC_KERNEL_LINUX_DIRENT_H
# define LIBC_KERNEL_LINUX_DIRENT_H


/* types */
# ifndef ino_t
#  define ino_t ino_t
typedef unsigned long long ino_t;
# endif
# ifndef off_t
#  define off_t off_t
typedef long long off_t;
# endif

struct dirent
{
	ino_t d_ino;
	off_t d_off;
	unsigned short int d_reclen;
	unsigned char d_type;
	char d_name[256]; /* NAME_MAX + 1 */
};

#endif /* !LIBC_KERNEL_LINUX_DIRENT_H */
